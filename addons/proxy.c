
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#define EXPORT_CALL EMSCRIPTEN_KEEPALIVE
#pragma message ("EMSCRIPTEN SUPPORT ENABLED")
#endif

typedef unsigned int widechar;

extern lou_dbfile_info lou_database_info[];

uint32_t EXPORT_CALL loureact_get_table_nbr (void)
{
    return (LOU_DATABASE_INFO_NBR);
}

char* EXPORT_CALL loureact_get_table_fname (uint_16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info->fname);
}

char* EXPORT_CALL loureact_get_table_description (uint_16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info->desc);
}

char* EXPORT_CALL loureact_get_table_lang (uint_16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info->lang);
}

char* EXPORT_CALL loureact_get_table_region (uint_16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info->region);
}

char* EXPORT_CALL loureact_get_table_flags (uint_16_t i)
{
    if (i < LOU_DATABASE_INFO_NBR)
        return (lou_database_info->flags);
}


int EXPORT_CALL test_lasterror (void)
{
    return _error;
}


