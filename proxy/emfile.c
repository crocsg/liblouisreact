
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#define EXPORT_CALL EMSCRIPTEN_KEEPALIVE
#pragma message ("EMSCRIPTEN SUPPORT ENABLED")
#endif
#include "loudatabase.h"
#include "internal.h"

extern lou_dbfile lou_database[];

#define ARRAYSIZE(a) (sizeof(a)/sizeof((a[0])))


// file handles
static LOU_FHANDLE _filesystem[EMFILE_HANDLE_NBR] = {0};

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
        return NULL;

    // find a free handle
    for (int i = 0; i < ARRAYSIZE(_filesystem); i++)
    {
        if (_filesystem[i].pdata == NULL)
        {
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


