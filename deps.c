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
    strlcpy(dep->name, name, sizeof(dep->name));
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
