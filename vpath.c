/** This is a -*-c-*- file
 **
 ** Copyright (c) 1994 LAAS/CNRS 
 ** Christophe Dousson - Fri Jun 17 1994
 **
 **/


#include "mkdep.h"
#include <string.h>
#include <stdlib.h>

#if HAVE_UNISTD_H
#   include <unistd.h>
#else
#   error("Not a POSIX system")
#endif

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
    char File[256];
    
    /* on teste le chemin courant */
    if (access(name, R_OK) == 0) {
	return NULL;
    }
    /* la, il faut tester tous les vpath possible */
    for (i = 0; i < nbpath; ++i) {
	strcpy(File, vpaths[i]);
	strcat(File, "/");
	strcat(File, name);
	if (access(File, R_OK) == 0) {
	    return vpaths[i];
	}
    }    
    fprintf (stderr, "mkdep: %s, file not found\n", name);
    exit(1);
    return NULL;
}
