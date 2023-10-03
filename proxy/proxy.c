
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifdef EMSCRIPTEM_SUPPORT
#include "emscripten.h"
#define EXPORT_CALL EMSCRIPTEN_KEEPALIVE
#pragma message ("EMSCRIPTEN SUPPORT ENABLED")

jhhjg gjhgjhgj ghj gjgjg
lkjjlk jlkj lk
#endif

#include "loudatabase.h"
#include "internal.h"

typedef unsigned int widechar;

extern lou_dbfile_info lou_database_info[];

static int _status = 0;
uint32_t EXPORT_CALL loureact_get_table_nbr (void)
{
    return (LOU_DATABASE_INFO_NBR);
}

char* EXPORT_CALL loureact_get_table_fname (uint16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
    {
        _lou_logMessage(LOU_LOG_WARN, "fname =>%s\n", lou_database_info[i].fname);
        return (lou_database_info[i].fname);
    }
    return NULL;
}

char* EXPORT_CALL loureact_get_table_description (uint16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info[i].desc);
    else
    {
        _lou_logMessage(LOU_LOG_WARN, "loureact_get_table_description index out of bound =>%d\n", i);
    }
    return NULL;
}

char* EXPORT_CALL loureact_get_table_lang (uint16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info[i].lang);
    return NULL;    
}

char* EXPORT_CALL loureact_get_table_region (uint16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info[i].region);
    return NULL;
}

uint16_t EXPORT_CALL loureact_get_table_flags (uint16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info[i].flags);
    return 0;
}

int EXPORT_CALL unicode_translate_get_status (void)
{
    return (_status);
}

widechar* EXPORT_CALL unicode_translate_string (widechar* src, int len, int tblid)
{
    widechar* pout = malloc(len * sizeof(widechar) * 2);
    int outlen = len * 2;
    char  tblist[256];
    
    snprintf (tblist, sizeof(tblist), "unicode.dis,%s", lou_database_info[tblid].fname);
       
    _lou_logMessage(LOU_LOG_WARN, "unicode_translate_string table=%s", tblist);
    _lou_logMessage(LOU_LOG_WARN, "unicode_translate_string len=%d", len);
    _lou_logMessage(LOU_LOG_WARN, "unicode_translate_string len bytes=%d", len * sizeof(widechar) * 2);

    _status = 0;
    memset (pout, 0, len * sizeof(widechar) * 2);
    int result = lou_translateString(tblist, src, &len,
		pout, &outlen, NULL, NULL, 0);
    _lou_logMessage(LOU_LOG_WARN, "lou_translateString ok");
    _status = result;

    return pout;
}




