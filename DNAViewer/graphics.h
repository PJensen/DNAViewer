//
//  graphics.h
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#ifndef DNAViewer_graphics_h
#define DNAViewer_graphics_h

#define GRAPHICS_WINDOW_TITLE "DNA Viewer"
#define GRAPHICS_CLEAR_COLOR 0.0,0.0,0.0,0.0
#define GRAPHICS_WINDOW_SIZE 1000,1000
#define GRAPHICS_WINDOW_POSITION 100,100
#define GRAPHICS_ORTHO -10.0, 10.0, -10.0, 10.0, -10.0, 10.0

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>

// Prototypes for init and callbacks.
void graphics_init(void);
void graphics_display(void);
void graphics_reshape(int w, int h);
void graphics_mouse(int b, int s, int x, int y);
void keyboard_func(unsigned char k, int x, int y);
void graphics_display_3d(void);

#endif
