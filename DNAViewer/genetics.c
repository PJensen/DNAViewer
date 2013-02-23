//
//  genetics.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include "dna_viewer.h"

const char AMINO_ACID[4] = {'T', 'C', 'G', 'A'};

const u_int8_t isAminoAcid(unsigned char value) 
{
    int index = 0x00;
    for (; index < 4; ++index) {
        if (value == AMINO_ACID[index])
            return 1;
    }
    return 0;
}

double pctT;
double pctC;
double pctG;
double pctA;
void calculateMetrics(void);
void calculateMetrics() 
{
    int t = 0,c = 0, g = 0, a = 0;
    
    for (int index = 0; index < DNAViewer.geneticDataSize; index++) 
    {
        switch (DNAViewer.geneticData[index]) 
        {
            case T: 
                t++;
                break;
            case C: 
                c++;
                break;
            case G: 
                g++;
                break;                
            case A: 
                a++;
                break;
        }
    }
    
    pctT = (1.0 * t / DNAViewer.geneticDataSize) * 100;
    pctC = (1.0 * c / DNAViewer.geneticDataSize) * 100;
    pctG = (1.0 * g / DNAViewer.geneticDataSize) * 100;
    pctA = (1.0 * a / DNAViewer.geneticDataSize) * 100;
    
    assert(t + c + g + a == DNAViewer.geneticDataSize);
    
    printf("Metrics: T(%.2f) C(%.2f) G(%.2f) A(%.2f)", pctT, pctC, pctG, pctA);
}

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
    DNAViewer.geneticDataMatchBuffer = (unsigned char*) malloc(sizeof(unsigned char) * tmpFileSize);
    
	//  Make sure we didn't run out of memory.
	if (DNAViewer.geneticData == NULL)
		doError("Out of memory.");
    
	// Read genetic data from input file.
	tmpReadResult = fread(DNAViewer.geneticData, 1, tmpFileSize, fp);
    
	// make sure the size of what was read and expected values match.
	if (tmpReadResult != tmpFileSize)
		doError("Input file read failure.");
    
	fclose(fp);
    
    DNAViewer.geneticDataSize = tmpFileSize;
    
	// Make sure the data ends up as upper case.
	for (index = 0; index < DNAViewer.geneticDataSize; ++index) 
    {
		*(DNAViewer.geneticData + index) = toupper(DNAViewer.geneticData[index]);
        
        if (!isAminoAcid(*(DNAViewer.geneticData + index)))
        {
            doError("Input file format error");
        }
    }
    
	printf("[Done]\n");
    
    calculateMetrics();
    
	return tmpFileSize;
}
