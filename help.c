/** This is a -*-c-*- file
 **
 ** Copyright (c) 1994 LAAS/CNRS 
 ** Christophe Dousson - Thu Jun 30 1994
 **
 **/


#include "mkdep.h"
#include <stdio.h>



static const char* helpLines[] = {
"Usage: mkdep [ -h ] [ -a ] [ -k ] [ -c <compiler> ]",
"             [ -l <target library> ] [ -d <target directory> ]",
"             [ -t <target suffix> ]  [ -p <source vpath> ]",
"             [ -i <ignored deps path> ] [ -o <output file> ]",
"             [ -I/-Y <directory> ] [ -D/-U <preproc. macros> ]",
"             [ -s <variable>=<subsituted path> ]  <files...>"
};

void display_help_message()
{
    int i;
    int nblines;
    nblines = sizeof(helpLines)/sizeof(char*);
    for (i = 0; i < nblines; ++i) {
	fprintf(stderr, "%s\n", helpLines[i]);
    }
}
