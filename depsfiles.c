/** This is a -*-c-*- file
 **
 ** Copyright (c) 1994 LAAS/CNRS 
 ** Christophe Dousson - Thu Jun 16 1994
 **
 **/

#include "mkdep.h"
#include <string.h>
#include <stdlib.h>

/*
 * Les dependances qu'on a trouve
 */

static deps * includedFiles = NULL;


void display_dependencies(FILE * fout, int compact, const char* target)
{
    deps * current = includedFiles;
    if (compact) {
	fprintf(fout, "%s", target);
	while (current != NULL) {
	    fprintf(fout, " %s", current->name);
	    current = current->next;
	}
	fprintf(fout, "\n\n");
    } else {
	while (current != NULL) {
	    fprintf(fout, "%s %s\n", target, current->name);
	    current = current->next;
	}
	fprintf(fout, "\n");
    }
}

void add_dependency(char name[256], const char * vpath, int vpathlength)
{
    deps * current;
    const char * addeddeps;

    /*
     * Filtrage des dependances (option -i, -s et le vpath)
     */
    if (ignore_filtering(name)) return;
    substitution_filtering(name);

    /* suppression du vpath (if any) */
    if ((vpathlength > 0) && 
	(strncmp(name, vpath, vpathlength) == 0) &&
	(name[vpathlength] == '/')) {
	addeddeps = name+vpathlength+1;
    } else {
	addeddeps = name;
    }
    /*
     * on range les dependances qu'on garde par ordre alphabetique
     */
    if (includedFiles == NULL) {
	includedFiles = new_deps(addeddeps, NULL);
    } else {
	int cmp = strcmp(addeddeps, includedFiles->name);
	if (cmp == 0) {
	    /* on l'avait deja */
	    return;
	}
	if (cmp < 0) {
	    includedFiles = new_deps(addeddeps, includedFiles);
	    return;
	}
	current = includedFiles;
	while (current->next != NULL) {
	    cmp = strcmp(addeddeps, current->next->name);
	    if (cmp == 0) {
		/* on l'avait deja */
		return;
	    }
	    if (cmp < 0) {
		/* on l'a pas, il faut la mettre ici */
		current->next = new_deps(addeddeps, current->next);
		return;
	    }
	    current = current->next;
	}
	/* on ajoute la nouvelle dependance en fin de la liste */
	current->next = new_deps(addeddeps, NULL);
    }
}

void reset_dependencies(void)
{
    delete_deps_list(includedFiles);
    includedFiles = NULL;
}
