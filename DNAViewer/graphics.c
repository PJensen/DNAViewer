//
//  graphics.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include "dna_viewer.h"

struct CoordT {
    int x;
    int y;
    int z;
} Coord;

void initCoord(void);

int slice = 0;

void initCoord()
{
    Coord.x = 0;
    Coord.y = 0;
    Coord.z = 0;
}

/**
 * Function: graphics_display
 * Description: Base display function; really meant as a place-holder.
 * Shows a line from bottom left, to top right and a box in the middle.
 */
void graphics_display()
{
    int index = 0x00;
    
    initCoord();
    
    // Clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
    
    glBegin(GL_LINE_STRIP);
    
    for (index = slice * 10000; index < (slice * 10000) + 10000 && (slice * 10000) + 10000 < DNAViewer.geneticDataSize; ++index)
    {        
        glVertex2f(Coord.x, Coord.y);
        
        switch (DNAViewer.geneticData[index]) 
        {
            case T:
                Coord.x++;
                break;
            case C:
                Coord.x--;
                break;
            case G:
                Coord.y--;
                break;
            case A:
                Coord.y++;
                break;
        }
    }
    
    glEnd();

	glFlush();
}

/**
 * Function: graphics_reshape
 * Description: Occurs when the window is reshaped.
 * Parameters:
 * 	w - Width
 *  h - Height
 */
void graphics_reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(GRAPHICS_ORTHO);
}

/**
 * Fires when the 'f' key is pressed; posts a redisplay.
 */
void keyboard_func(unsigned char k, int x, int y)
{
    int bSlice = 0;
	switch (k) {
        case 'd':
        case 'D':
            if (slice + 1 < DNAViewer.geneticDataSize)
                slice++;
            bSlice = 1;
            break;
        case 'a':
        case 'A':
            if (slice > 0)
                slice--;
            bSlice = 1;
            break;
		default:
			break;
	}
    
    glutPostRedisplay();
    
    if (bSlice) 
        debug("Showing slice: (%d)", slice);
	debug("keyhit: (%d)", k);
}

/**
 * Mouse function
 */
void graphics_mouse(int b, int s, int x, int y)
{
	debug("click: (%d,%d) B:%d", x, y, b);
}

/**
 * Function: graphics_init
 * Description: Initialize OpenGL
 */
void graphics_init()
{    
	// glut initialization
	glutInit(&DNAViewer.argc, DNAViewer.argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(GRAPHICS_WINDOW_SIZE);
	glutInitWindowPosition(GRAPHICS_WINDOW_POSITION);
	glutCreateWindow(GRAPHICS_WINDOW_TITLE);
    
	// Initialize extents, color, matrix mode.
	glClearColor(GRAPHICS_CLEAR_COLOR);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	glOrtho(GRAPHICS_ORTHO);
    
	// Register reshape and draw functions.
	glutReshapeFunc(graphics_reshape);
	glutKeyboardFunc(keyboard_func);
    glutMouseFunc(graphics_mouse);
    glutDisplayFunc(graphics_display);
}
