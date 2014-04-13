#ifndef SOMEAPI
	#define SOMEAPI
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int SIZE = 11;

	char * dtoa(char *s, double n);
	void text(char* string);
	
	void drawAxis(void);
	
	void keyboard(unsigned char key, int x, int y);
	
#endif 
