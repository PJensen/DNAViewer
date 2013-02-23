//
//  dna_viewer.h
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#ifndef DNAViewer_dna_viewer_h
#define DNAViewer_dna_viewer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>

#include "graphics.h"
#include "genetics.h"
#include "error.h"
#include "debug.h"

struct DNAViewerT {
    char **argv;
    int argc;
    unsigned char* geneticData;
    size_t geneticDataSize;
    char fileName[255];
};

// extern struct DNAViewerT DNAViewer;

struct DNAViewerT DNAViewer;

#endif
