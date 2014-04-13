#include "lagrange.h"
#include "spline.hpp"
#include <GL/glut.h>
#include "quanc8.h"
#include "function.hpp"
#include <iostream>

double func(double x);
double func1(double x);
double func2(double x);
void render(void);
void render1(void);
void render2(void);
void creategraph(int main, void(*func)(void), int xpos, int ypos, int xpos1, int ypos1,float x, float y);

char* argv[] = {"GLUT_RGB", "-w", "GLUT_RGBA"};
int argc = 3;

LagrangePolynomial* lg = new LagrangePolynomial();
Function* fun = new Function(func, 10);
Spline* spl = new Spline(fun->getx(), fun->gety());

int main()
{
	std::cout << "Initial func:" << std::endl;
	fun->print_to_console();
	
	//spline
	std::cout << std::endl << "Spline:" << std::endl;
	double u = 0.0, s, t, e;
	while(u < fun->getx().at(fun->getx().size()-1))
	{
		s = spl->seval(&u);
		t = func(u);
		e = fabs(t-s);
		std::cout << "U=" << u << "\tS=" << s << "\tT=" << t << "\tErr=" << e << std::endl;
		spl->ux.push_back(u);
		spl->tx.push_back(t);
		u = u + 0.15;
	}
	
	//lagrange
	std::cout << std::endl << "Lagrange Polynomial values" << std::endl;
	//std::cout << "X\t" << "Approximate" << "\tExect" << "\tError" << std::endl;
	std::cout.precision(8);
	for(unsigned int i = 0; i < 20; i++)
	{
		lg->setx(i*0.15);
		lg->sety(lg->fi(lg->getlastx(), fun->getx(), fun->gety()));
		e = fabs(lg->getlasty() - func(lg->getlastx()));
		std::cout 
			<< "X=" << lg->getlastx() 
			<< "\tApproximate = " << lg->getlasty() 
			<< "\tExect = " << func(lg->getlastx()) 
			<< "\tError = " << e
			<< std::endl;
	}
	
	//Integral
	int nofun, k = 1;
	double a = 0.5, b = 1.0, abserr = 0.0, relerr = 1.0e-6, result, errest, flag;
	
	std::cout << std::endl << "Integral value for m = -0.5" << std::endl;
	std::cout << "K\t" << "Result\t" << "Errest\t" << "\tflag\t" << "Nofun" << std::endl;
	while(k < 101.1)
	{
		quanc8(func1, a,b, abserr, relerr, result, errest, nofun, flag);
		std::cout << k << "\t" << result << "\t" << errest << "\t" << flag << "\t" << nofun << std::endl;
		k = k + 10;
	}
	
	k = 1;
	std::cout << std::endl << "Integral value for m = -1" << std::endl;
	std::cout << "K\t" << "Result\t" << "Errest\t" << "\tflag\t" << "Nofun" << std::endl;
	while(k < 101.1)
	{
		quanc8(func2, a,b, abserr, relerr, result, errest, nofun, flag);
		std::cout << k << "\t" << result << "\t" << errest << "\t" << flag << "\t" << nofun << std::endl;
		k = k + 10;
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1350, 450);
	glutInitWindowPosition(10, 10);

	int main = glutCreateWindow("Graph");
		creategraph(main, render, 0,0, 450,450, 3.5,1.5);
		creategraph(main, render1, 450,0, 450,450, 3.5,1.5);
		creategraph(main, render2, 900,0, 450,450, 3.5,1.5);
	glutMainLoop();
	
	return 0;
}

void creategraph(int main, void(*func)(void), int xpos, int ypos, int xpos1, int ypos1,float x, float y)
{
	glutCreateSubWindow(main, xpos,ypos, xpos1, ypos1);
	glOrtho(-x,x, -y, y, 0.0,3.0);
	//glOrtho(0,x, 0,y, -1.0,1.0);
	glutDisplayFunc(func);
}

void render(void)
{
	spl->graph();
}

void render1(void)
{
	lg->graph();
}

void render2(void)
{
	fun->graph();
}

double func(double x)
{
	return 1 - exp(-x);
}

double func1(double x)
{
	double m = -0.5;
	return pow(fabs(sin(x) - 0.6), m);
}

double func2(double x)
{
	double m = -1;
	return pow(fabs(sin(x) - 0.6), m);
}
