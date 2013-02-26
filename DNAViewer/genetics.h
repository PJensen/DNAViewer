//
//  genetics.h
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#ifndef DNAViewer_genetics_h
#define DNAViewer_genetics_h

#define T7Promoter "TAATACGACTCACTATAGG"
#define SP6Promoter "ATTTAGGTGACACTATAG"
#define T3Promoter "ATTAACCCTCACTAAAGGG"
#define M13Forward "GTTGTAAAACGACGGCCAGT"
#define M13Reverse "TCACACAGGAAACAGCTATGA"
#define AP4Oligo "CCCCTGTGAGGAACT"
#define U19Oligo "GTTTTCCCAGTCACGACGT"
#define HIS6 "CATCATCACCATCACCAC"
#define FLAGEpitope "GATTACAAGGATGACGACGATAAG"
#define ExpressEpitope "GATCTGTACGACGATGACGATAAG"

#define T   'T'
#define C   'C'
#define G   'G'
#define A   'A'

#define IS_AMINO_ACID(x)   (toupper(x) == 'T' || toupper(x) == 'C' || toupper(x) == 'G' || toupper(x) == 'A')

#define MATCH_PATTERN_MAX_LEN   2048
#define MATCH_PATTERN_NAME_LEN  64

typedef struct  {
    char patternName[MATCH_PATTERN_NAME_LEN];
    char matchAcids[MATCH_PATTERN_MAX_LEN];
    int matchAcidLength;
    unsigned int match;
} GeneticPatternT;

typedef struct {
    char* sequencePtr;
    GeneticPatternT pattern;
} MatchedPatternT;

void initPatterns(void);
void patternDetectionFirstPass(void);
void initPattern(const char* name, const char* sequence);
void patternDetectionFirstPass();
const u_int8_t isAminoAcid(char value);
const long readGeneticData(void);
void calculateMetrics(void);


#endif
