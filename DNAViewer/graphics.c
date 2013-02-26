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
    
	glClear(GL_COLOR_BUFFER_BIT);
    
	glColor3f(1.0, 1.0, 1.0);
    
    glBegin(GL_TRIANGLE_STRIP);
    
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

void graphics_display_3d()
{
    int index = 0x02;
    
    initCoord();
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
    
    glPushMatrix();

    glBegin(GL_TRIANGLE_STRIP);
    
    for (; index < 1000; index += 2)
    {
        char D[2] = "";
                
        D[0] = DNAViewer.geneticData[index - 2];
        D[1] = DNAViewer.geneticData[index - 1];
        
        struct CoordT vector;
        
        vector.x = 0;
        vector.y = 0;
        vector.z = 0;
        
        switch(D[1])
        {
            case 'T':      
                vector.x = 1;
                vector.y = 1;
                glColor3f(1.0, 1.0, 1.0);
                break;
            case 'C':
                vector.x = -1;
                vector.y = 1;
                glColor3f(1.0, 0.0, 0.0);
                break;
            case 'G':
                vector.x = -1;
                vector.y = -1;
                glColor3f(0.0, 1.0, 0.0);
                break;
            case 'A':
                vector.x = 1;
                vector.y = -1;
                glColor3f(0.0, 0.0, 1.0);
                break;       
        }
        
        switch(D[0])
        {
            case 'T':      
                vector.z = -1;
                break;
            case 'C':
                vector.z = 0;
                break;
            case 'A':
                vector.z = 1;
                break;
            case 'G':
                switch(D[1])
            {
                case 'T':    
                    vector.x = -1;
                    vector.y = 0;
                    vector.z = 0;
                    break;
                case 'C':
                    vector.x = 0;
                    vector.y = 0;
                    vector.z = -1;
                    break;
                case 'G':
                    vector.x = 1;
                    vector.y = 0;
                    vector.z = 0;
                    break;
                case 'A':
                    vector.x = 0;
                    vector.y = 0;
                    vector.z = -1;
                    break;       
            }
                break;
        }
    
        
        Coord.x += vector.x;
        Coord.y += vector.y;
        Coord.z += vector.z;
        
        glVertex3i(Coord.x, Coord.y, Coord.z);
        
        // lutSolidSphere(1, 5, 5);
    }
    
    glEnd();
    
//    glBegin(GL_TRIANGLES);
//    
//    glVertex3i(20, 10, 10);
//    glVertex3i(10, 20, 10);
//    glVertex3i(10, 10, 20);
//    
//    glEnd();
     
    glPopMatrix();
    
    glutSwapBuffers();
    glutPostRedisplay();
    
    //glRotated(1, rand(), 0, 0);
    //glRotated(1, 0, rand(), 0);
    // glRotated(1, 0, 0, rand());
    
    
    
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
    gluPerspective(60, w / h, 1, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(50, 50, 50, 0, 0, 0, 0, 1, 0);
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
    glRotated(1, rand(), 0, 0);
}

/**
 * Function: graphics_init
 * Description: Initialize OpenGL
 */
void graphics_init()
{    
	// glut initialization
	glutInit(&DNAViewer.argc, DNAViewer.argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(GRAPHICS_WINDOW_SIZE);
	glutInitWindowPosition(GRAPHICS_WINDOW_POSITION);
	glutCreateWindow(GRAPHICS_WINDOW_TITLE);
    
	// Initialize extents, color, matrix mode.
	glClearColor(GRAPHICS_CLEAR_COLOR);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	// Register reshape and draw functions.
	glutReshapeFunc(graphics_reshape);
	glutKeyboardFunc(keyboard_func);
    glutMouseFunc(graphics_mouse);
    glutDisplayFunc(graphics_display_3d);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

/**
 // TT, TC, TG, TA
 if (strncmp(D, "TT", 2) == 0) 
 {
 vector.x = 1;
 vector.y = 1;
 vector.z = -1;
 }
 else if (strncmp(D, "TC", 2) == 0) 
 {
 vector.x = 1;
 vector.y = -1;
 vector.z = 1; 
 }
 else if (strncmp(D, "TG", 2) == 0) 
 {
 vector.x = -1;
 vector.y = -1;
 vector.z = 1; 
 }
 else if (strncmp(D, "TA", 2) == 0) 
 {
 vector.x = -1;
 vector.y = -1;
 vector.z = 1; 
 }
 // CT, CC, CG, CA
 else if (strncmp(D, "CT", 2) == 0) 
 {
 vector.x = 0;
 vector.y = 0;
 vector.z = 0; 
 }
 else if (strncmp(D, "CC", 2) == 0) 
 {
 vector.x = 0;
 vector.y = 0;
 vector.z = 0; 
 }
 else if (strncmp(D, "CG", 2) == 0) 
 {
 vector.x = 0;
 vector.y = 0;
 vector.z = 0; 
 }
 else if (strncmp(D, "CA", 2) == 0) 
 {
 vector.x = 0;
 vector.y = 0;
 vector.z = 0; 
 }
 // GT, GC, GG, GA
 else if (strncmp(D, "GT", 2) == 0) 
 {
 
 }
 else if (strncmp(D, "GC", 2) == 0) 
 {
 
 }
 else if (strncmp(D, "GG", 2) == 0) 
 {
 
 }
 else if (strncmp(D, "GA", 2) == 0) 
 {
 
 }
 // AT, AC, AG, AA
 else if (strncmp(D, "AT", 2) == 0) 
 {
 
 }
 else if (strncmp(D, "AC", 2) == 0) 
 {
 
 }
 else if (strncmp(D, "AG", 2) == 0) 
 {
 
 }
 else if (strncmp(D, "AA", 2) == 0) 
 {
 
 }
 else 
 {
 assert(0);
 }**/
