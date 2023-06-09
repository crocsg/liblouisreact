// Autogenerated file
// Do not manually modify
// file:./liblouisreact/database/loudatabase.h



#ifndef	__LOUDATABASE_H_H
#define	__LOUDATABASE_H_H


#define	LOU_DBFILE_NBR	417
#define	LOU_DATABASE_INFO_NBR	201
#define	LOU_DATABASE_DISPLAY_NBR	24


typedef struct _lou_dbfile{
	char *fname;
	uint8_t* data;
	size_t* size;
} lou_dbfile;


typedef struct _lou_dbfile_info{
	char     *fname;
	char     *desc;
	char     *lang;
	char     *region;
	uint16_t  flags;
} lou_dbfile_info;
#endif


