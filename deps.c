/** This is a -*-c-*- file
 **
 ** Copyright (c) 1994 LAAS/CNRS 
 ** Christophe Dousson - Thu Jun 16 1994
 **
 **/

#include "mkdep.h"
#include <string.h>
#include <stdlib.h>


/* les allocations deja faites */
static deps * allocQueue = NULL;


deps * new_deps(const char* name, deps * next)
{
    deps * dep;
    if (allocQueue == NULL) {
	/* on en alloue plusieurs (10) d'un coup */
	int i;
	allocQueue = (deps*) malloc(sizeof(deps) * 10);
	for (i = 0; i < 9; ++i) {
	    allocQueue[i].next = &(allocQueue[i+1]);
	}
	allocQueue[9].next = NULL;
    } 
    dep = allocQueue;
    allocQueue = allocQueue->next;
    strcpy(dep->name, name);
    dep->next = next;
    dep->length = strlen(name);
    return dep;
}

void delete_deps_list(deps * list)
{
    if (list != NULL) {

	deps * current = list;
	while (current->next != NULL) {
	    current = current->next;
	}
	current->next = allocQueue;
	allocQueue = list;
    }
}
