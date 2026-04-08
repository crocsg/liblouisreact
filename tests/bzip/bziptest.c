#include <stdio.h>
#include "loudatabase.h"

extern lou_dbfile lou_database[];

#define ARRAYSIZE(a) (sizeof(a)/sizeof((a[0])))


int main (void)
{
    for (int i = 0;i < ARRAYSIZE(lou_database);i++)
    {
        printf ("filename : %s\n",lou_database[i].fname);
    }
    return (0);
}