#include "lagrange.h"
#include "someapi.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iterator>
#include <iostream>

LagrangePolynomial::LagrangePolynomial()
{}

LagrangePolynomial::~LagrangePolynomial()
{}
 
double LagrangePolynomial::fi(double X, 
                              const std::vector< double > & x,
                              const std::vector< double > & y)
{
    double sum = 0.0;
	double basic = 1.0;

	for(unsigned int i = 0; i < x.size(); i++)
	{
		basic = 1.0;
		for(unsigned int j = 0; j < x.size(); j++)
		{
			if( j == i) continue;
			basic *= (X - x[j]) / (x[i] - x[j]);
		}
		sum += basic * y[i];
	}
    return sum;
}

void LagrangePolynomial::setx(double x)
{
	xx.push_back(x);
}

void LagrangePolynomial::sety(double y)
{
	yy.push_back(y);
}

double LagrangePolynomial::getlastx(void)
{
	return xx.back();
}

double LagrangePolynomial::getlasty(void)
{
	return yy.back();
}

void LagrangePolynomial::graph(void)
{
	char s[32];
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	drawAxis();

	glRasterPos2f(-1, 1.3);
	text("Graph Lagrange Polynominal");

	glRasterPos2f(xx.back(), 0.1);
	text("X");
	glRasterPos2f(-0.2, yy.back());
	glFlush();
	
	for(auto iterx = begin(xx), itery = begin(yy); iterx != end(xx), itery != end(yy); iterx++, itery++)
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
		for(auto iterx = begin(xx), itery = begin(yy); iterx != end(xx), itery != end(yy); iterx++, itery++)
		{
			glVertex2d(*iterx, *itery);
		}
	glEnd();
	glFlush();
}
