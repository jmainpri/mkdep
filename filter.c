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
#include <string.h>
#include <stdlib.h>

static deps * substitutions = NULL;


void add_substitution(const char* subst)
{
    deps * newsubst = new_deps(subst, NULL);

    { /* on cherche le signe '=' de la substitution */
	int pos = 0;
	while (subst[pos] != '=') {
	    if (subst[pos] == 0) {
		fprintf(stderr,
			"mkdep: bad argument for -s option: %s\n", subst);
		return;
	    }
	    ++ pos;
	}
	newsubst->name[pos] = 0;
	newsubst->subname = newsubst->name + pos +1;
	newsubst->length = strlen(newsubst->subname);
    }
    /* la liste substitutions a un entete vide */
    if (substitutions == NULL) {
	substitutions = new_deps("(null)", NULL);
    }
    {  /* il faut ajouter les substitutions en ordre alphabetique inverse
	* pour effectuer les plus longues possibles a chaque fois */

	deps * current = substitutions;
	while ((current->next != NULL) &&
	       strcmp(newsubst->subname, current->next->subname) < 0) {
	    current = current->next;
	}
	if (current->next == NULL) {
	    /* ajout en fin de liste */
	    current->next = newsubst;
	} else if (strcmp(newsubst->subname, current->next->subname) > 0) {
	    newsubst->next = current->next;
	    current->next = newsubst;
	} else {
	    if (strcmp(newsubst->name, current->next->name) != 0) {
		fprintf(stderr, 
			"mkdep: $(%s) and $(%s) define the same path \"%s\"\n",
			newsubst->name, current->next->name, newsubst->subname);
	    }
	    delete_deps_list(newsubst);
	}
    }
}


void substitution_filtering(char name[256])
{
    deps * current = NULL;
    if (substitutions != NULL) {
	current = substitutions->next; /* entete vide dans la liste */
    }
    while (current != NULL) {
	if (strncmp(current->subname, name, current->length) == 0) {
	    char result[256];
	    sprintf(result, "$(%s)%s", current->name, name+current->length);
	    strcpy(name, result);
	}
	current = current->next;
    }
}

/*----------------------------------------------------------------------*/

/*
 * Les include systeme qu'on ne veut pas recuperer
 */
static char* sysDeps[] = {
    "/usr/include",
    "/usr/local/include",
    "/usr/local/openwin/include",
    "/usr/openwin/include",
    "/opt",
    "/local/gnu",
    "/usr/local/gnu",
    "/usr/local/lib/gcc-lib",
    "/usr/lib/gcc-lib"
};

/*
 * Les chemins de dependances qu'on doit refuser (option -i)
 */

static deps * systemPaths = NULL;
static deps * userPaths = NULL;

#define  CMP(dep,file) strncmp(dep->name, file, dep->length)


int ignore_filtering(const char * name)
{
    deps * current;
    /*
     * on recherche si la dependance est l'une du systeme
     * on une propre a l'utilisateur
     */
    current = systemPaths;    
    while (current != NULL) {
        /* si c'est un include du system, on ne le prend pas */
        if (CMP(current, name) == 0) return 1;
        current = current->next;
    }
    current = userPaths;
    while (current != NULL) {
        /* si c'est un include ignore par l'utilisateur, on s'en va */
        if (CMP(current, name) == 0) return 1;
        current = current->next;
    }
    return 0;
}


/*
 *   gestion des options -i et -a 
 */

void generate_system_dependencies(void)
{
    /* et donc la boucle autour de sysDeps ne se fera pas */
    delete_deps_list(systemPaths);
    systemPaths = NULL;
}

void ignore_system_dependencies(void)
{ 
    if (systemPaths == NULL) {
	int i;
	int nbSysDeps = sizeof(sysDeps)/sizeof(char*);
	for (i = 0; i < nbSysDeps; ++i) {
	    systemPaths = new_deps(sysDeps[i], systemPaths);
	}
    }
}

void ignore_user_dependency(const char * name)
{
    userPaths = new_deps(name, userPaths);
}
