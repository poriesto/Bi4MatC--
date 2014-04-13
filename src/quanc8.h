#ifndef _QUANC8
	#define _QUANC8

void quanc8(double(*fun)(double), double a, double b,
            double abserr, double relerr, double& result, 
			double& errest, int& nofun,double& flag);

#endif //_QUANC8
