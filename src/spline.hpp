#include <vector>
#include <math.h>
#include <iterator>

class Spline
{
private:
	std::vector<double>x, y;
	std::vector<double> b, c, d;
	
	void spline();
public:
	std::vector<double>ux, tx;
public:
	Spline(std::vector<double>x, std::vector<double>y);
	double seval(double* u);
	void graph(void);
	~Spline();
};

