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



#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "mkdep.h"


static char  * vpath = NULL;
static char ** vpaths = NULL;
static int     nbpath = 0;

void define_vpath(const char* value)
{
    /* on supprimme l'ancien VPATH */
    if (vpath != NULL) {
	free(vpath);
	free(vpaths);
	vpath = NULL;
	nbpath = 0;
    }
    if ((value != NULL) && (value[0] != 0)) {
	int pos = 0;
	int index;
	vpath = strdup(value);
	/* on compte le nombre de chemins */
	nbpath = 1;
	while (vpath[pos] != 0) {
	    if (vpath[pos] == ':') {
		nbpath ++;
	    }
	    pos ++;
	}
	vpaths = (char**) malloc(sizeof(char*)*nbpath);
	vpaths[0] = vpath;
	/* on remplace les ':' et les ' ' par des 0 */
	pos = 0;
	index = 0;
	while (vpath[pos] != 0) {
	    if ((vpath[pos] == ':') || (vpath[pos] == ' ')) {
		vpath[pos] = 0;
		if (vpaths[index] != vpath+pos) {
		    ++ index;
		}
		vpaths[index] = vpath+pos+1;
	    }
	    pos ++;
	}
    }
}


const char* find_file(const char* name)
{
    int i;
    char File[1024];
    
    /* on teste le chemin courant */
    if (access(name, R_OK) == 0) {
	return NULL;
    }
    /* la, il faut tester tous les vpath possible */
    for (i = 0; i < nbpath; ++i) {
	    strlcpy(File, vpaths[i], sizeof(File));
	    strlcat(File, "/", sizeof(File));
	    strlcat(File, name, sizeof(File));
	    if (access(File, R_OK) == 0) {
		    return vpaths[i];
	    }
    }    
    fprintf (stderr, "mkdep: %s, file not found\n", name);
    exit(1);
    return NULL;
}
