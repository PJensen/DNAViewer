//
//  main.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "graphics.h"
#include "debug.h"
#include "dna_viewer.h"

void parseArgs(void);
void initialize(int argc, char** argv);

int main (int argc, char ** argv)
{
    initialize(argc, argv);
    glutPostRedisplay();
    glutMainLoop();

    return EXIT_SUCCESS;
}

/**
 * Function: initialize
 * Description: takes the initial parameters passed to the program
 *  sets up the global struct, parses program arguments and initializes
 *  the OpenGL graphics context.
 */
void initialize(int argc, char** argv) 
{
    DNAViewer.argv = argv;
    DNAViewer.argc = argc;
    
    parseArgs();
    graphics_init();
}

/**
 * Function: parseArgs
 * Description: Parse arguments and populate the parameters struct with
 * settings pulled from argv.
 * Remarks: argv and argc are not modified.
 */
void parseArgs()
{
	// Define various parameters for command line usage.
	const char* FILENAME_PARAM = "-f";
	const char* HELP_PARAM = "-help";
    
	int index;
    
	// Index through all arguments
	for (index = 0; index < DNAViewer.argc; ++index)
		if (strcmp(FILENAME_PARAM, DNAViewer.argv[index]) == 0) {
			if (DNAViewer.argv[index + 1] != '\0')
				strcat(DNAViewer.fileName, DNAViewer.argv[index + 1]);
		} else if (strcmp(HELP_PARAM, DNAViewer.argv[index]) == 0) {
			//(void) showHelp();
			exit(EXIT_SUCCESS);
		}
    
	// Show various settings.
    if (DNAViewer.fileName != NULL)
        printf("\n\nFilename: %s\n", DNAViewer.fileName);
    else
        printf("\n\nFilename: (null)\n");
}


