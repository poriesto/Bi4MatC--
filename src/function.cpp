#include "function.hpp"
#include "someapi.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

Function::Function(double(*func)(double), unsigned int N)
{
	for(unsigned int i = 0; i < N; i++)
	{
		x.push_back(i*0.3);
		y.push_back(func(x.back()));
	}
}

void Function::print_to_console(void)
{
	for(auto iterx = begin(x), itery = begin(y); 
			 iterx != end(x), itery != end(y);
			 iterx++, itery++)
	{
		std::cout << "x = " << *iterx << "\ty = " << *itery << std::endl;
	}

}

std::vector<double>Function::getx(void)
{
	return x;
}

std::vector<double>Function::gety(void)
{
	return y;
}

void Function::graph(void)
{
	char s[32];
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	drawAxis();

	glRasterPos2f(-1, 1.3);
	text("Graph init funtion");

	glRasterPos2f(x.back(), 0.1);
	text("X");
	glRasterPos2f(-0.2, y.back());
	glFlush();
	
	for(auto iterx = begin(x), itery = begin(y);
		   	iterx != end(x), itery != end(y);
		   	iterx++, itery++)
	{
		glRasterPos2f(0.0, *itery);
		text("-");
		glRasterPos2f(0.004, *itery);
		text(dtoa(s, *itery));

		glRasterPos2f(*iterx, -0.01);
		text("|");
		glRasterPos2f(*iterx, 0.009);
		text(dtoa(s, *iterx));
	}
	glFlush();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
		for(auto iterx = begin(x), itery = begin(y); 
				iterx != end(x), itery != end(y);
			   	iterx++, itery++)
		{
			glVertex2d(*iterx, *itery);
		}
	glEnd();
	glFlush();
}
