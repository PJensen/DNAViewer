//
//  dna_viewer.h
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#ifndef DNAViewer_dna_viewer_h
#define DNAViewer_dna_viewer_h

struct DNAViewerT {
    char **argv;
    int argc;
    char *fileName;
    unsigned char* geneticData;
};

// extern struct DNAViewerT DNAViewer;

struct DNAViewerT DNAViewer;

#endif
