//
//  genetics.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include "genetics.h"

/**
 * Function: readGeneticData
 * Description: Reads genetic data
 * Returns: The number of bytes in the data sequence.
 * Postconditions:
 *	The value of geneticData will be populated with the genetic data.
 */
const long readGeneticData()
{
	FILE* fp;				// Input file pointer
	long tmpFileSize;		// The size of the file; figure out before hand.
	size_t tmpReadResult;	// The result of doing fread on the file.
	int index;
    
	// Show that were about to read in genetic data.
	printf("Reading genetic data ... ");
    
	// Try to open params.fileName, exit on failure.
	if ((fp = fopen(DNAViewer.fileName, "r")) == NULL)
		doError("Input file does not exist.");
    
	// Determine the file's size, set as a long value.
	fseek(fp, 0, SEEK_END);
	tmpFileSize = ftell(fp);
	rewind(fp);
    
	// Allocate a chunk of memory that is exactly the size of the input file.
	DNAViewer.geneticData = (unsigned char*) malloc(sizeof(unsigned char) * tmpFileSize);
    
	//  Make sure we didn't run out of memory.
	if (DNAViewer.geneticData == NULL)
		doError("Out of memory.");
    
	// Read genetic data from input file.
	tmpReadResult = fread(DNAViewer.geneticData, 1, tmpFileSize, fp);
    
	// make sure the size of what was read and expected values match.
	if (tmpReadResult != tmpFileSize)
		doError("Input file read failure.");
    
	fclose(fp);
    
	// Make sure the data ends up as upper case.
	for (index = 0; index < tmpFileSize; ++index)
		*(DNAViewer.geneticData + index) = toupper(DNAViewer.geneticData[index]);
    
	printf("[Done]\n");
    
	return tmpFileSize;
}
