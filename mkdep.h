/*  This looks like c, but it's really -*-c-*-
 * 
 * Copyright (c) 1994-2003 LAAS/CNRS 
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
 */


#ifndef MKDEP_H
#define MKDEP_H

#include <stdio.h>

typedef struct deps {
    char           name[1024];
    char *         subname; /* pour l'option -s */
    int            length;
    struct deps*   next;
} deps;


void            display_help_message        ();

/* strings 'deps' manager */

deps *          new_deps                    (const char *, deps *);
void            delete_deps_list            (deps *);


/* dependancies manager */

void            display_dependencies        (FILE *, int, const char*);
void            add_dependency              (char *name, size_t namelen, 
                                             const char*, int);
void            reset_dependencies          (void);



/* preprocessing manager */

void            parse_preprocessed_data     (FILE*, const char*);

void            define_preprocessor         (const char *);
void            add_preprocessor_arg        (char, const char*);
FILE *          run_preprocessor            (const char*, const char*);


/* vpath manager */

void            define_vpath                (const char*);
const char*     find_file                   (const char*);


/* filtering manager */

void            add_substitution            (const char*);
void            substitution_filtering      (char *name, size_t namelen);

int             ignore_filtering            (const char *);         
void            ignore_user_dependency      (const char *);
void            ignore_system_dependencies  (void);
void            generate_system_dependencies(void);


/* output file */

FILE *          open_output_file            (const char*);
void            display_target              (FILE*, int, 
					     char*, const char*,
					     const char*, const char*);
void            close_output_file           (FILE*);

void            interrupt_dependancies      (int);

#endif  /* ! MKDEP_H */


