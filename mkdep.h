/*  This looks like c, but it's really -*-c-*-
 * 
 *  Copyright (C) 1994 LAAS/CNRS 
 *  Christophe Dousson - Thu Jun 16 1994
 */


#ifndef MKDEP_H
#define MKDEP_H

#include <stdio.h>

typedef struct deps {
    char           name[256];
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
void            add_dependency              (char name[256], const char*, int);
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
void            substitution_filtering      (char name[256]);

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


