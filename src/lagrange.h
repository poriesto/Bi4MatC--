//lagrange.h
#ifndef LAGRANGE_H
#define LAGRANGE_H
 
#include <vector>

class LagrangePolynomial {
public:
	LagrangePolynomial();
	~LagrangePolynomial();	
    double fi(double X, 
                     const std::vector< double > & x, 
                     const std::vector< double > & y);
    void setx(double x);
	void sety(double y);
	double getlastx(void);
	double getlasty(void);
	void graph(void);
//private:
	std::vector<double>xx, yy;
};
#endif // LAGRANGE_H
