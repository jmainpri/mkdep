/** This is a -*-c-*- file
 **
 ** Copyright (c) 1994 LAAS/CNRS 
 ** Christophe Dousson - Thu Jun 16 1994
 **
 **/

#include "mkdep.h"
#include <signal.h>

int main(int argc, char** argv)
{
    int arg = 1;
    int compact = 0;
    char * argument = NULL; /* de l'option */
    char * library = NULL;
    char * directory = NULL;
    char * suffix = "o";
    FILE * fout = NULL;

    /* traitement des interruptions */
    signal(SIGINT, interrupt_dependancies);
    signal(SIGQUIT, interrupt_dependancies);

    /* par defaut, on ignore les dependances des fichiers systemes */
    ignore_system_dependencies();

    /* traitement des arguments */
    while (arg < argc) {

	/* traitement des options */
	if (argv[arg][0] == '-') {
	    /* on se place sur l'arg. suivant (pour l'option avec arg.) */
	    if (argv[arg][2] != 0) {
		argument = argv[arg]+2;
	    } else {
		if (arg+1 < argc) {
		    argument = argv[arg+1];
		} else {
		    argument = NULL;
		}
	    }

	    switch (argv[arg][1]) {
		
	      case 'a':
		generate_system_dependencies();
		argument = NULL; /* on ne l'utilise pas */
		break;
		
	      case 'k':
		compact = 1;
		argument = NULL; /* on ne l'utilise pas */
		break;

	      case 'd':
		directory = argument;
		break;
		
	      case 'o':
		close_output_file(fout);
		fout = open_output_file(argument);
		break;
		
	      case 'l':
		library = argument;
		break;
		
	      case 'i':
		ignore_user_dependency(argument);
		break;

	      case 's':
		add_substitution(argument);
		break;

	      case 't':
		suffix = argument;
		if (argument[0] == '.') suffix++;
		break;

	      case 'p': /* vpath */
		if (strcmp(argv[arg], "-pthread") == 0) {
		    /* option -pthread de gcc */
		    add_preprocessor_arg(argv[arg][1], argument);
		} else {
		    define_vpath(argument);
		}
		break;

	      case 'c':
		define_preprocessor(argument);
		library = NULL;
		directory = NULL;
		break;

	      case 'h':
		display_help_message();
		exit(0);
		break;
				
	      case 'I': /* options du preprocesseur */
	      case 'D':
	      case 'U':
	      case 'Y':
		add_preprocessor_arg(argv[arg][1], argument);
		break;

	      case 'm':
		if (strcmp(argv[arg], "-mt") == 0) {
		    /* option -mt de Sun WorkShop */
		    add_preprocessor_arg(argv[arg][1], argument);
		    break;
		} 
		/*FALLTHROUGH*/
	      default:
		fprintf(stderr, "mkdep unknown option: %s\n", argv[arg]);
		break;
	    }
	} else {
	    /* traitement des fichiers */
	    if (fout == NULL) {
		/* on envoie tout sur la sortie standard (stdout) */
		fout = open_output_file(NULL);
	    }
	    display_target(fout, compact,
			   argv[arg], directory, library, suffix);
	}
	/* on passe a l'argument suivant */
	/* (on pense a sauter les args. des options) */
	arg ++;
	if ((argument != NULL) && (argv[arg] == argument)) {
	    arg ++;
	}
    }
    close_output_file(fout);
    exit(0);
}
