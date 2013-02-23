//
//  error.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "dna_viewer.h"

/**
 * Function: doError
 * Description: Prints an error message to standard error.
 * Parameters: aErrorMessage - The error message to put to standard error.
 */
void doError(const char* aErrorMessage)
{
	fprintf(stderr, "%s", aErrorMessage);
	exit(EXIT_FAILURE);
}
