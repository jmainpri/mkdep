/** This is a -*-c-*- file
 **
 ** Copyright (c) 1994 LAAS/CNRS 
 ** Christophe Dousson - Fri Jun 17 1994
 **
 **/


#include "mkdep.h"
#include <ctype.h>

static char * preprocessor = NULL;


void define_preprocessor(const char * name)
{
    if (preprocessor) {
	free(preprocessor);
	preprocessor = NULL;
    }
    if (name != NULL) {
	preprocessor = (char*) malloc(strlen(name)+4);
	sprintf(preprocessor, "%s -E", name);
    }
}

void add_preprocessor_arg(char opt, const char *arg)
{
    if (preprocessor == NULL) {
	define_preprocessor(CC); /* CC = MACRO */
    }
    preprocessor = (char*) realloc(preprocessor,
				   strlen(preprocessor)+strlen(arg)+4);
    sprintf(preprocessor+strlen(preprocessor),
	    " -%c%s", opt, arg);
}

FILE * run_preprocessor(const char* file, const char *vpath)
{
    FILE * fin;
    char * command;
    if (preprocessor == NULL) {
	define_preprocessor(CC); /* CC = MACRO */
    }
    if (vpath == NULL) {
	command = (char*) malloc(strlen(preprocessor)+strlen(file)+7);
	sprintf(command, "exec %s %s", preprocessor, file);
    } else {
	command = (char*) malloc(strlen(preprocessor)+
				 +strlen(vpath)+strlen(file)+8);
	sprintf(command, "exec %s %s/%s", preprocessor, vpath, file);
    }
    fin = popen(command, "r");
    free(command);
    return fin;
}

/*
 * Les dependances se trouve avec les lignes de preprocesseur
 * de format: # 23 "titi.c"
 */
void parse_preprocessed_data(FILE * fin, const char * vpath)
{
    char buffer[256];
    int len = 0;
    int c = '\n'; 
    if (vpath != NULL) {
	len = strlen(vpath);
    }
    while (c != EOF) {
	if (c == '\n') {
	    c = getc(fin);
	    /* ligne du preprocesseur, commence par '#' */
	    if (c == '#') {
		/* on supprimme les blancs */
		do { c = getc(fin); } while (c == ' ');
		/* on verifie que c'est bien un numero de ligne */
		if (isdigit(c)) {
		    /* on supprimme les chiffres puis les blancs */
		    while (isdigit(c)) { 
			c = getc(fin); 
		    } 
		    if (c != ' ') {
			/* il faut un blanc la` !
			   s'il y a autre chose c'est dans le programme
			   et des fois ca commence par "...." */
			continue;
		    }
		    while (c == ' ') { 
			c = getc(fin); 
			
		    } 
		    /* on doit avoir une double quote sinon c'est que
		       c'est pas la ligne qu'on croyait */
		    if (c == '"') {
			int pos = 0;
			do {
			    c = getc(fin);
			    buffer[pos++] = c;
			} while (c != '"' && c != '\n' && c != EOF);
			if (c == '"') {
			    /* tout s'est bien passe */
			    buffer[pos-1] = 0;
			    add_dependency(buffer, vpath, len);
			} else {
			    /* probleme mais quoi ??? */
			}
		    } /* fin de (c == '"') */
		} /* fin de (c == '1') */
	    } /* fin de (c == '#') */
	} else {
	    c = getc(fin);
	}
    } /* fin du while */
}

