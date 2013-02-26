//
//  graphics.c
//  DNAViewer
//
//  Created by Pete Jensen on 2/21/13.
//  Copyright (c) 2013 PJensen. All rights reserved.
//

#include "dna_viewer.h"

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_position[] = { 50.0, 50, 50, 125 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };


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
    
    // initCoord();
    
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
    int index = 0x02 * slice;
    
    initCoord();
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();

    glBegin(GL_LINE_STRIP);
    
    glColor4f(0.0, 0.0, 0.0, 1);
    for (; index < (10000 * slice) + 100; index += 2)
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
    
        vector.x *= 5;
        vector.y *= 5;
        vector.z *= 5;
    
        Coord.x += vector.x;
        Coord.y += vector.y;
        Coord.z += vector.z;
        
        glVertex3i(Coord.x, Coord.y, Coord.z);
    }
    
    glEnd();
    
//    glBegin(GL_TRIANGLES);
//    
//    glVertex3i(20, 10, 10);
//    glVertex3i(10, 20, 10);
//    glVertex3i(10, 10, 20);
//    
//    glEnd();
     gluLookAt(150,150,150, Coord.x, Coord.y, Coord.z, 0, 0, 1);
    
    glPopMatrix();
    
     
    
    // glLoadIdentity();
    
    //gluLookAt(0, 0, 0, Coord.x, Coord.y, Coord.z, 0, 1, 0);
    glutSwapBuffers();
    glutPostRedisplay();
    
    // gluLookAt(50, 50, 50, 0, 0, 0, 0, 1, 0);
    //
    
    
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
    gluPerspective(30, w / h, 1, 20000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //gluLookAt(Coord.x, Coord.y, Coord.z,150,150,150, 0, 0, 1);
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
	debug("click: (%d,%d) B:%d S: %d", x, y, b, s);
    
    switch (b) {
        case 0:
            glRotated(10, 1, 0, 0);
            break;
        case 1:
            glRotated(10, 0, 1, 0);
            break;
        case 2:
            glRotated(10, 0, 0, 1);
            break;
        default:
            break;
    }
}

/**
 * Function: graphics_init
 * Description: Initialize OpenGL
 */
void graphics_init()
{    
	// glut initialization
	glutInit(&DNAViewer.argc, DNAViewer.argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    GLfloat lmodel_ambient[] = { 1.2, 1.2, 1.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
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
