/** This is a -*-c-*- file **/
/*
 * Copyright (c) 1994 LAAS/CNRS 
 * Christophe Dousson - Thu Jun 16 1994
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


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
