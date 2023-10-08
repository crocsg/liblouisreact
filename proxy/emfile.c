/* liblouisreact 

   This file is part of liblouisreact .

   liblouisreact is a webassembly proxy to access liblouis library and table
   from react.js

   liblouisreact is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 2.1 of the License, or
   (at your option) any later version.
   
   You should have received a copy of the GNU Lesser General Public
   License along with liblouisreact. If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#define EXPORT_CALL EMSCRIPTEN_KEEPALIVE

#endif

#include "loudatabase.h"
#include "internal.h"

extern lou_dbfile lou_database[];

#define ARRAYSIZE(a) (sizeof(a)/sizeof((a[0])))


// file handles
static LOU_FHANDLE _filesystem[EMFILE_HANDLE_NBR] = {0};
static char _asked_file[8192] = {0};

int emstat(const char *path, struct stat *buf)
{
    lou_dbfile* pdata = NULL;
    _lou_logMessage(LOU_LOG_WARN, "fstat %s", path);
    // find the requested file
    for (int i = 0; i < LOU_DBFILE_NBR; i++)
    {
        if (strcmp (lou_database[i].fname, path) == 0)
        {
            _lou_logMessage(LOU_LOG_WARN, "fstat %s=>%s", path, lou_database[i].fname);
            pdata = &lou_database[i];
            break;
        }
    }
    if (pdata == NULL)
        return -1;
 
    memset (buf, 0, sizeof(struct stat));
    buf->st_size = *(pdata->size);
    buf->st_mode = S_IFREG;

    return (0);
}

LOU_FHANDLE *emfopen(const char *filename, const char *mode)
{
    lou_dbfile* pdata = NULL;

    // find the requested file
    for (int i = 0; i < LOU_DBFILE_NBR; i++)
    {
        
        if (strcmp (lou_database[i].fname, filename) == 0)
        {
            pdata = &lou_database[i];
            break;
        }
    }

    if (pdata == NULL)
    {
        _lou_logMessage(LOU_LOG_WARN, "fopen %s not found", filename)
        return NULL;
    }

    // find a free handle
    for (int i = 0; i < ARRAYSIZE(_filesystem); i++)
    {
        if (_filesystem[i].pdata == NULL)
        {
            _lou_logMessage(LOU_LOG_WARN, "fopen %s", filename);
            _filesystem[i].pdata = pdata->data;
            _filesystem[i].size = *(pdata->size);
            _filesystem[i].offset = 0;
            return (&_filesystem[i]);
        }
    }

    return (NULL);
}

int emfgetc(LOU_FHANDLE *stream)
{
    if (stream->pdata == NULL)
        return (-2);

    if (stream->offset < stream->size)
    {
        uint8_t data = stream->pdata[stream->offset];
        stream->offset++;
        return ((int) data);
    }
    else
        return (EOF);

    return 0;
}

int emfclose(LOU_FHANDLE *stream)
{
    stream->pdata = NULL;
    stream->size = 0;
    stream->offset = 0;
    return (0);
}


