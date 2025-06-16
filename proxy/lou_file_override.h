#ifndef __LOU_FILE_OVERRIDE_H
#define __LOU_FILE_OVERRIDE_H

#pragma message ("EMSCRIPTEM_SUPPORT ENABLED")


#define LOU_FHANDLE EMFILE
#define LOU_FGETC emfgetc
#define LOU_FOPEN emfopen
#define LOU_FCLOSE emfclose
#define LOU_STAT emstat
#define EMFILE_HANDLE_NBR	64

#endif // __LOU_FILE_OVERRIDE_H