#include <vector>
#include <iterator>

class Function
{
	private:
		std::vector<double>x, y;
	public:
		Function(double(*func)(double), unsigned int N);
		std::vector<double> getx(void);
		std::vector<double> gety(void);
		void print_to_console(void);
		void graph(void);
};
