/** This is a -*-c-*- file **/
/*
 * Copyright (c) 1994-2004 LAAS/CNRS 
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

void add_dependency(char *name, size_t namelen, 
    const char * vpath, int vpathlength)
{
    deps * current;
    const char * addeddeps;

    /*
     * Filtrage des dependances (option -i, -s et le vpath)
     */
    if (ignore_filtering(name)) return;
    substitution_filtering(name, namelen);

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
