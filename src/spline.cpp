// spline.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//
#include "spline.hpp"
#include "someapi.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>

Spline::Spline(std::vector<double>x, std::vector<double>y)
{
	for (unsigned int i = 0; i < x.size(); i++)
	{
		b.push_back(0);
		c.push_back(0);
		d.push_back(0);
	}
	this->x = x; this->y = y;
	spline();
}


Spline::~Spline()
{
}

void Spline::spline()
{
	int i, ib, nm1, n = x.size()-1;
	double t;

	nm1 = n - 1;
	if (n < 2)  return;
	if (n < 3)  goto l20;
	d[1] = x[2] - x[1];
	c[2] = (y[2] - y[1]) / d[1];
	for (i = 2; i <= nm1; i++)
	{
		d[i] = x[i + 1] - x[i];
		b[i] = 2 * (d[i - 1] + d[i]);
		c[i + 1] = (y[i + 1] - y[i]) / d[i];
		c[i] = c[i + 1] - c[i];
	}
	b[1] = -d[1];
	b[n] = -d[n - 1];
	c[1] = 0;
	c[n] = 0;
	if (n == 3) goto l10;
	c[1] = c[3] / (x[4] - x[2]) - c[2] / (x[3] - x[1]);
	c[n] = c[n - 1] / (x[n] - x[n - 2]) - c[n - 2] / (x[n - 1] - x[n - 3]);
	c[1] = c[1] * sqrt(d[1]) / (x[4] - x[1]);
	c[n] = -c[n] * sqrt(d[n - 1]) / (x[n] - x[n - 3]);

l10:    for (i = 2; i <= n; i++)
{
	t = d[i - 1] / b[i - 1];
	b[i] = b[i] - t*d[i - 1];
	c[i] = c[i] - t*c[i - 1];
}
		c[n] = c[n] / b[n];
		for (ib = 1; ib <= nm1; ib++)
		{
			i = n - ib;
			c[i] = (c[i] - d[i] * c[i + 1]) / b[i];
		}
		b[n] = (y[n] - y[nm1]) / d[nm1] + d[nm1] * (c[nm1] + 2 * c[n]);
		for (i = 1; i <= nm1; i++)
		{
			b[i] = (y[i + 1] - y[i]) / d[i] - d[i] * (c[i + 1] + 2 * c[i]);
			d[i] = (c[i + 1] - c[i]) / d[i];
			c[i] = 3 * c[i];
		}
		c[n] = 3 * c[n];
		d[n] = d[n - 1];
		return;
	l20:  b[1] = (y[2] - y[1]) / (x[2] - x[1]);
		c[1] = 0;
		d[1] = 0;
		b[2] = b[1];
		c[2] = 0;
		d[2] = 0;
}

double Spline::seval(double u)
{
	int i, j, k, n = x.size()-1;
	double dx;
	i = 0;
	if (i >= n) i = 1;
	if (u < x[i]) goto l10;
	if (u > x[i]) goto l10;
	if (u <= x[i + 1]) goto l30;

l10: i = 1;
	j = n + 1;


l20: k = (i + j) / 2;
	if (u < x[k]) j = k;
	if (u >= x[k]) i = k;
	if (j >(i + 1)) goto l20;

l30: dx = u - x[i];
	return y[i] + dx*(b[i] + dx*(c[i] + dx*d[i]));
}

void Spline::graph()
{
	char s[32];
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);
	drawAxis();
	
	glRasterPos2f(-1, 1.3);
	text("Graph spline function");


	glRasterPos2f(ux[10], 0.1);
	text("X");
	glRasterPos2f(-0.2, tx[9]);
	text("Y");
    glFlush();

	for(auto iterux = begin(ux), itertx = begin(tx); iterux != end(ux), itertx != end(tx); iterux++, itertx++)
	{
		glRasterPos2f(0.0, *itertx);
		text("-");
		glRasterPos2f(0.004, *itertx);
		text(dtoa(s, *itertx));

		glRasterPos2f(*iterux, -0.01);
		text("|");
		glRasterPos2f(*iterux, 0.009);
		text(dtoa(s, *iterux));

	}

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
		for(auto iterux = begin(ux), itertx = begin(tx); iterux != end(ux), itertx != end(tx); iterux++, itertx++)
		{
			glVertex2d(*iterux, *itertx);
		}
	glEnd();
	glFlush();
}
