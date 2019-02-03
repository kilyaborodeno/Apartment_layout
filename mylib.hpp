#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <cstdlib>       // rand, srand

int pick_of_two(int a, int b)
{
	bool r = std::rand() % 2;
	return a*r + b*(!r);
}


double max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

#endif // MYLIB_HPP
