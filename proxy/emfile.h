/* liblouisreact 

   This file is part of liblouisreact .

   liblouisreact is a webassembly proxy for accesing liblouis library and table
   from react.js

   liblouisreact is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 2.1 of the License, or
   (at your option) any later version.
   
   You should have received a copy of the GNU Lesser General Public
   License along with liblouisreact. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __EMFILE_H
#define __EMFILE_H

#include <sys/stat.h>
#include "emscripten.h"
#include "emscripten/stack.h"

typedef struct _EMFILE 
{
	uint8_t* 	pdata;
	size_t 	offset;
	size_t	size;
} EMFILE;

EMFILE *emfopen(const char *filename, const char *mode);
int emfgetc(EMFILE *stream);
int emfclose(EMFILE *stream);
int emstat(const char *path, struct stat *buf);

#pragma message ("EMSCRIPTEM EMFILE.H LOADED")

#endif // __EMFILE_H