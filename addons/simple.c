
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


#if 0
int main (void)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf ("%d %d %d\n", i,j, test_add(i,j));
        }
    }
}




int EXPORT_CALL test_add (int x, int y)
{
    return x + y;
}

static widechar buf[16384];

static int widestrlen(widechar* str)
{
    int cnt = 0;
    for (widechar* p = str; *p != 0; p++)
        cnt+=4;
    return(cnt);
}

int EXPORT_CALL set_str (widechar *test, int maxlength)
{
    memset (buf, 0, sizeof(buf));
    int len = widestrlen(test);
    len = maxlength;
    memcpy (buf, test, len > sizeof(buf) ? sizeof(buf): len);    
    return (sizeof(widechar));
}

widechar* EXPORT_CALL  get_str (void)
{
    int len = widestrlen (buf);
    widechar *ptr = (widechar *) malloc ((len + 1) * 4);
    memcpy (ptr, buf, (len + 1) * 4);
    return (ptr);
}
#endif