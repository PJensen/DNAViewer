//
//  genetics.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include "dna_viewer.h"

const char AMINO_ACID[4] = {'T', 'C', 'G', 'A'};

/**
 * Description: Initializes well known patterns 
 * TODO: These should be read from a file or files.
 */
void initPatterns() 
{
    DNAViewer.knownPatterns = 1;
    DNAViewer.geneticPatterns = malloc(sizeof(GeneticPatternT) * DNAViewer.knownPatterns);
    if (DNAViewer.geneticPatterns == NULL)
        doError("Out of memory.");
    
    initPattern("HIS6", HIS6);
    
    initPattern("T7Promoter", T7Promoter);
    initPattern("SP6Promoter", SP6Promoter);
    initPattern("T3Promoter", T3Promoter);
    
    initPattern("M13Forward", M13Forward);
    initPattern("M13Reverse", M13Reverse);
    initPattern("AP4Oligo", AP4Oligo);
    
    initPattern("U19Oligo", U19Oligo);
    initPattern("FLAGEpitope", FLAGEpitope);
    initPattern("ExpressEpitope", ExpressEpitope);
        
    initPattern("CMVPromoter","TAGTAATCAATTACGGGGTCATTAGTTCATAGCCCATATATGGAGTTCCGCGTTACATAACTTACGGTAAATGGCCCGCCTGGCTGACCGCCCAACGACCCCCGCCCATTGACGTCAATAATGACGTATGTTCCCATAGTAACGCCAATAGGGACTTTCCATTGACGTCAATGGGTGGAGTATTTACGGTAAACTGCCCACTTGGCAGTACATCAAGTGTATCATATGCCAAGTACGCCCCCTATTGACGTCAATGACGGTAAATGGCCCGCCTGGCATTATGCCCAGTACATGACCTTATGGGACTTTCCTACTTGGCAGTACATCTACGTATTAGTCATCGCTATTACCATGGTGATGCGGTTTTGGCAGTACATCAATGGGCGTGGATAGCGGTTTGACTCACGGGGATTTCCAAGTCTCCACCCCATTGACGTCAATGGGAGTTTGTTTTGGCACCAAAATCAACGGGACTTTCCAAAATGTCGTAACAACTCCGCCCCATTGACGCAAATGGGCGGTAGGCGTGTACGGTGGGAGGTCTATATAAGCAGAGCTGGTTTAGTGAACCGTCAG");
    
    initPattern("Ampicillin", "atgagtattcaacatttccgtgtcgcccttattcccttttttgcggcattttgccttcctgtttttgctcacccagaaacgctggtgaaagtaaaagatgctgaagatcagttgggtgcacgagtgggttacatcgaactggatctcaacagcggtaagatccttgagagttttcgccccgaagaacgttttccaatgatgagcacttttaaagttctgctatgtggcgcggtattatcccgtgttgacgccgggcaagagcaactcggtcgccgcatacactattctcagaatgacttggttgagtactcaccagtcacagaaaagcatcttacggatggcatgacagtaagagaattatgcagtgctgccataaccatgagtgataacactgcggccaacttacttctgacaacgatcggaggaccgaaggagctaaccgcttttttgcacaacatgggggatcatgtaactcgccttgatcgttgggaaccggagctgaatgaagccataccaaacgacgagcgtgacaccacgatgcctgcagcaatggcaacaacgttgcgcaaactattaactggcgaactacttactctagcttcccggcaacaattaatagactggatggaggcggataaagttgcaggaccacttctgcgctcggcccttccggctggctggtttattgctgataaatctggagccggtgagcgtgggtctcgcggtatcattgcagcactggggccagatggtaagccctcccgtatcgtagttatctacacgacggggagtcaggcaactatggatgaacgaaatagacagatcgctgagataggtgcctcactgattaagcattggtaa");
    
    initPattern("BGH polyA","TGTGCCTTCTAGTTGCCAGCCATCTGTTGTTTGCCCCTCCCCCGTGCCTTCCTTGACCCTGGAAGGTGCCACTCCCACTGTCCTTTCCTAATAAAATGAGGAAATTGCATCGCATTGTCTGAGTAGGTGTCATTCTATTCTGGGGGGTGGGGTGGGGCAGGACAGCAAGGGGGAGGATTGGGAAGACAATAGCAGGCATGCTGGGGATGCGGTGGGCTCTATGGC");
    
    initPattern("SV40 ORI", "CTGTGGAATGTGTGTCAGTTAGGGTGTGGAAAGTCCCCAGGCTCCCCAGCAGGCAGAAGTATGCAAAGCATGCATCTCAATTAGTCAGCAACCAGGTGTGGAAAGTCCCCAGGCTCCCCAGCAGGCAGAAGTATGCAAAGCATGCATCTCAATTAGTCAGCAACCATAGTCCCGCCCCTAACTCCGCCCATCCCGCCCCTAACTCCGCCCAGTTCCGCCCATTCTCCGCCCCATGGCTGACTAATTTTTTTTATTTATGCAGAGGCCGAGGCCGCCTCTGCCTCTGAGCTATTCCAGAAGTAGTGAGGAGGCTTTTTTGGAGGCCTAGGCTTTTGCAAAAAGCTC");
    
    initPattern("SV40 polyAr", "ACTTGTTTATTGCAGCTTATAATGGTTACAAATAAAGCAATAGCATCACAAATTTCACAAATAAAGCATTTTTTTCACTGCATTCTAGTTGTGGTTTGTCCAAACTCATCAATGTATCTTATCATGTCTGT");
    
    initPattern("Yellow Florescent Protien", "ATGGTGAGCAAGGGCGAGGAGCTGTTCACCGGGGTGGTGCCCATCCTGGTCGAGCTGGACGGCGACGTAAACGGCCACAAGTTCAGCGTGTCCGGCGAGGGCGAGGGCGATGCCACCTACGGCAAGCTGACCCTGAAGTTCATCTGCACCACCGGCAAGCTGCCCGTGCCCTGGCCCACCCTCGTGACCACCTTCGGCTACGGCCTGCAGTGCTTCGCCCGCTACCCCGACCACATGAAGCAGCACGACTTCTTCAAGTCCGCCATGCCCGAAGGCTACGTCCAGGAGCGCACCATCTTCTTCAAGGACGACGGCAACTACAAGACCCGCGCCGAGGTGAAGTTCGAGGGCGACACCCTGGTGAACCGCATCGAGCTGAAGGGCATCGACTTCAAGGAGGACGGCAACATCCTGGGGCACAAGCTGGAGTACAACTACAACAGCCACAACGTCTATATCATGGCCGACAAGCAGAAGAACGGCATCAAGGTGAACTTCAzGATCCGCCACAACATCGAGGACGGCAGCGTGCAGCTCGCCGACCACTACCAGCAGAACACCCCCATCGGCGACGGCCCCGTGCTGCTGCCCGACAACCACTACCTGAGCTACCAGTCCGCCCTGAGCAAAGACCCCAACGAGAAGCGCGATCACATGGTCCTGCTGGAGTTCGTGACCGCCGCCGGGATCACTCTCGGCATGGACGAGCTGTACAAGTAA");
    
    initPattern("Glutathione-S-Transferase", "ATGTCCCCTATACTAGGTTATTGGAAAATTAAGGGCCTTGTGCAACCCACTCGACTTCTTTTGGAATATCTTGAAGAAAAATATGAAGAGCATTTGTATGAGCGCGATGAAGGTGATAAATGGCGAAACAAAAAGTTTGAATTGGGTTTGGAGTTTCCCAATCTTCCTTATTATATTGATGGTGATGTTAAATTAACACAGTCTATGGCCATCATACGTTATATAGCTGACAAGCACAACATGTTGGGTGGTTGTCCAAAAGAGCGTGCAGAGATTTCAATGCTTGAAGGAGCGGTTTTGGATATTAGATACGGTGTTTCGAGAATTGCATATAGTAAAGACTTTGAAACTCTCAAAGTTGATTTTCTTAGCAAGCTACCTGAAATGCTGAAAATGTTCGAAGATCGTTTATGTCATAAAACATATTTAAATGGTGATCATGTAACCCATCCTGACTTCATGTTGTATGACGCTCTTGATGTTGTTTTATACATGGACCCAATGTGCCTGGATGCGTTCCCAAAATTAGTTTGTTTTAAAAAACGTATTGAAGCTATCCCACAAATTGATAAGTACTTGAAATCCAGCAAGTATATAGCATGGCCTTTGCAGGGCTGGCAAGCCACGTTTGGTGGTGGCGACCATCCTCCAAAATCGGATCTGGTTCC");
    
    initPattern("'Eukaryotic' Green Fluorescent Protein", "ATGGTGAGCAAGGGCGAGGAGCTGTTCACCGGGGTGGTGCCCATCCTGGTCGAGCTGGACGGCGACGTAAACGGCCACAAGTTCAGCGTGTCCGGCGAGGGCGAGGGCGATGCCACCTACGGCAAGCTGACCCTGAAGTTCATCTGCACCACCGGCAAGCTGCCCGTGCCCTGGCCCACCCTCGTGACCACCCTGACCTACGGCGTGCAGTGCTTCAGCCGCTACCCCGACCACATGAAGCAGCACGACTTCTTCAAGTCCGCCATGCCCGAAGGCTACGTCCAGGAGCGCACCATCTTCTTCAAGGACGACGGCAACTACAAGACCCGCGCCGAGGTGAAGTTCGAGGGCGACACCCTGGTGAACCGCATCGAGCTGAAGGGCATCGACTTCAAGGAGGACGGCAACATCCTGGGGCACAAGCTGGAGTACAACTACAACAGCCACAACGTCTATATCATGGCCGACAAGCAGAAGAACGGCATCAAGGTGAACTTCAAGATCCGCCACAACATCGAGGACGGCAGCGTGCAGCTCGCCGACCACTACCAGCAGAACACCCCCATCGGCGACGGCCCCGTGCTGCTGCCCGACAACCACTACCTGAGCACCCAGTCCGCCCTGAGCAAAGACCCCAACGAGAAGCGCGATCACATGGTCCTGCTGGAGTTCGTGACCGCCGCCGGGATCACTCTCGGCATGGACGAGCTGTACAAG");
    
    initPattern("F1 Ori", "GCGCCCTGTAGCGGCGCATTAAGCGCGGCGGGTGTGGTGGTTACGCGCAGCGTGACCGCTACACTTGCCAGCGCCCTAGCGCCCGCTCCTTTCGCTTTCTTCCCTTCCTTTCTCGCCACGTTCGCCGGCTTTCCCCGTCAAGCTCTAAATCGGGGGCTCCCTTTAGGGTTCCGATTTAGTGCTTTACGGCACCTCGACCCCAAAAAACTTGATTAGGGTGATGGTTCACGTAGTGGGCCATCGCCCTGATAGACGGTTTTTCGCCCTTTGACGTTGGAGTCCACGTTCTTTAATAGTGGACTCTTGTTCCAAACTGGAACAACACTCAACCCTATCTCGGTCTATTCTTTTGATTTATAAGGGATTTTGCCGATTTCGGCCTATTGGTTAAAAAATGAGCTGATTTAACAAAAATTTAACGCGAATTA");
    
    initPattern("mCherry (RFP)", "atggtgagcaagggcgaggaggataacatggccatcatcaaggagttcatgcgcttcaaggtgcacatggagggctccgtgaacggccacgagttcgagatcgagggcgagggcgagggccgcccctacgagggcacccagaccgccaagctgaaggtgaccaagggtggccccctgcccttcgcctgggacatcctgtcccctcagttcatgtacggctccaaggcctacgtgaagcaccccgccgacatccccgactacttgaagctgtccttccccgagggcttcaagtgggagcgcgtgatgaacttcgaggacggcggcgtggtgaccgtgacccaggactcctccctgcaggacggcgagttcatctacaaggtgaagctgcgcggcaccaacttcccctccgacggccccgtaatgcagaagaagaccatgggctgggaggcctcctccgagcggatgtaccccgaggacggcgccctgaagggcgagatcaagcagaggctgaagctgaaggacggcggccactacgacgctgaggtcaagaccacctacaaggccaagaagcccgtgcagctgcccggcgcctacaacgtcaacatcaagttggacatcacctcccacaacgaggactacaccatcgtggaacagtacgaacgcgccgagggccgccactccaccggcggcatggacgagctgtacaagtaa");
    
    
    initPattern("tdTomato (RFP - dimer)", "atggtgagcaagggcgaggaggtcatcaaagagttcatgcgcttcaaggtgcgcatggagggctccatgaacggccacgagttcgagatcgagggcgagggcgagggccgcccctacgagggcacccagaccgccaagctgaaggtgaccaagggcggccccctgcccttcgcctgggacatcctgtccccccagttcatgtacggctccaaggcgtacgtgaagcaccccgccgacatccccgattacaagaagctgtccttccccgagggcttcaagtgggagcgcgtgatgaacttcgaggacggcggtctggtgaccgtgacccaggactcctccctgcaggacggcacgctgatctacaaggtgaagatgcgcggcaccaacttcccccccgacggccccgtaatgcagaagaagaccatgggctgggaggcctccaccgagcgcctgtacccccgcgacggcgtgctgaagggcgagatccaccaggccctgaagctgaaggacggcggccactacctggtggagttcaagaccatctacatggccaagaagcccgtgcaactgcccggctactactacgtggacaccaagctggacatcacctcccacaacgaggactacaccatcgtggaacagtacgagcgctccgagggccgccaccacctgttcctggggcatggcaccggcagcaccggcagcggcagctccggcaccgcctcctccgaggacaacaacatggccgtcatcaaagagttcatgcgcttcaaggtgcgcatggagggctccatgaacggccacgagttcgagatcgagggcgagggcgagggccgcccctacgagggcacccagaccgccaagctgaaggtgaccaagggcggccccctgcccttcgcctgggacatcctgtccccccagttcatgtacggctccaaggcgtacgtgaagcaccccgccgacatccccgattacaagaagctgtccttccccgagggcttcaagtgggagcgcgtgatgaacttcgaggacggcggtctggtgaccgtgacccaggactcctccctgcaggacggcacgctgatctacaaggtgaagatgcgcggcaccaacttcccccccgacggccccgtaatgcagaagaagaccatgggctgggaggcctccaccgagcgcctgtacccccgcgacggcgtgctgaagggcgagatccaccaggccctgaagctgaaggacggcggccgctacctggtggagttcaagaccatctacatggccaagaagcccgtgcaactgcccggctactactacgtggacaccaagctggacatcacctcccacaacgaggactacaccatcgtggaacagtacgagcgctccgagggccgccaccacctgttcctgtacggcatggacgagctgtacaagtaa");
    
    DNAViewer.knownPatterns--;
}

/**
 * Description: Initializes a single pattern
 * Precondition: Name and pattern are under buffer size length(s) 
 * Side Effects: Will make pattern to-upper
 */
void initPattern(const char* name, const char* sequence)
{
    assert(strlen(name) < MATCH_PATTERN_NAME_LEN);
    assert(strlen(sequence) < MATCH_PATTERN_MAX_LEN);
    
    DNAViewer.geneticPatterns = realloc(DNAViewer.geneticPatterns, 
        sizeof(GeneticPatternT) * DNAViewer.knownPatterns);
    
    GeneticPatternT* pattern = &DNAViewer.geneticPatterns[DNAViewer.knownPatterns - 1];
    
    strcpy(pattern->patternName, name);
    strcpy(pattern->matchAcids, sequence);
    
    pattern->matchAcidLength = strlen(pattern->matchAcids);
    
    for(int index = 0; index < pattern->matchAcidLength; ++index) 
        pattern->matchAcids[index] = toupper(pattern->matchAcids[index]);
    
    DNAViewer.knownPatterns++;
}

/**
 * Given a letter determine if it's an amino acid
 */
const u_int8_t isAminoAcid(char value) 
{
    int index = 0x00;
    for (; index < 4; ++index) {
        if (value == AMINO_ACID[index])
            return 1;
    }
    return 0;
}

/**
 * Description: Quick hack towards sub-pattern detection.
 */
void patternDetectionFirstPass()
{    
    for (int index = 0; index < DNAViewer.geneticDataSize; index++)
    {
        char acid = DNAViewer.geneticData[index];
        
        for(int p = 0; p < DNAViewer.knownPatterns; p++)
        {
            GeneticPatternT* match = &DNAViewer.geneticPatterns[p];
            
            match->match = 0x01;
            
            for(int c = 0; c < match->matchAcidLength; c++)
            {
                if (match->match)
                {
                    match->match = match->matchAcids[c] == acid;
                }
                else 
                {
                    match->match = 0;
                    
                    break;
                }
            }
            
            if (match->match)
            {
                assert(match->patternName != NULL);
                
                debug("Matched: %s at DNA Sequence #: %d", 
                      match->patternName, index);
            }
            
            match->match = 1;
        }
    }
}

/**
 * Description: Calculates the percentage distribution for TCGAs
 */
void calculateMetrics() 
{
    double pctT, pctC, pctG, pctA;
    int t = 0, c = 0, g = 0, a = 0;
    
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
    
    printf("\nMetrics: T(%.2f) C(%.2f) G(%.2f) A(%.2f)\n", pctT, pctC, pctG, pctA);
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
	DNAViewer.geneticData = (char*) malloc(sizeof(unsigned char) * tmpFileSize);
    DNAViewer.geneticDataMatchBuffer = (char*) malloc(sizeof(unsigned char) * tmpFileSize);
    
	//  Make sure we didn't run out of memory.
	if (DNAViewer.geneticData == NULL || DNAViewer.geneticDataMatchBuffer == NULL)
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
