//
//  debug.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include "debug.h"

/**
 * Function: graphics_debug
 * Description: debug strings to standard error
 */
void debug(const char* format, ...)
{   
#if DEBUG
    const int BUFF_SIZE = 256;
    char dest[BUFF_SIZE];
    
    int lenAccum = strlen(format);
    if (lenAccum > BUFF_SIZE)
        return;
    
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(dest, BUFF_SIZE, format, argptr);
    lenAccum += strlen(dest);
    va_end(argptr);
    
    if (lenAccum + 1 > BUFF_SIZE || lenAccum > BUFF_SIZE)
        return;
    
    strncat(dest, "\n", BUFF_SIZE);
    
    fprintf(stderr, "%s", dest);
#endif
}
