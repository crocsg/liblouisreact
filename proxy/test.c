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
#include "emfile.h"


widechar* EXPORT_CALL test_translate_fr (widechar* src, int len)
{
    lou
}

char* EXPORT_CALL test_file (void)
{
    uint8_t *tbuf = malloc(8192);
    memset (tbuf, 0, 8192);
    LOU_FHANDLE* fdata = emfopen ("bel.utb", NULL);
    if (fdata == NULL)
        return NULL;
    int p = 0;
    int data;
    while ((data = emfgetc (fdata)) != EOF)
        tbuf[p++] = (char) data;
    
    emfclose (fdata);
    
    return ((char *)tbuf);
}