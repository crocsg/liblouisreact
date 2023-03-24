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

static int _error;

int EXPORT_CALL test_lasterror (void)
{
    return _error;
}

widechar* EXPORT_CALL test_translate_fr (widechar* src, int len)
{
    widechar* pout = malloc(len * sizeof(widechar) * 2);
    int outlen = len * 2;
    char* tblist ="unicode.dis,fr-bfu-comp6.utb";
    
    _lou_logMessage(LOU_LOG_WARN, "test_translate_fr len=%d", len);
    _lou_logMessage(LOU_LOG_WARN, "test_translate_fr len bytes=%d", len * sizeof(widechar) * 2);

    _error = 0;
    memset (pout, 0, len * sizeof(widechar) * 2);
    int result = lou_translateString(tblist, src, &len,
		pout, &outlen, NULL, NULL, 0);
    
    if (result)
        _error = result;

    return pout;
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