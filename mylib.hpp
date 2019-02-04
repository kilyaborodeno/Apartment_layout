#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <cstdlib>       // rand, srand
#include <vector>

using namespace std;

int pick_of_two(int a, int b)
{
	bool r = rand() % 2;
	return a*r + b*(!r);
}

double max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

bool sides_at_wall(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
    bool sides = false;
    if(x1 == X1)
        sides = true;
    if(y1 == Y1)
        sides = true;
    if(y2 == Y2)
        sides = true;
    if(x2 == X2)
        sides = true;
    return sides;
}

int which_sides_free(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
    int sides = 0;
    if(x1 != X1)
        sides *= 10 + 1; // left
    if(y1 != Y1)
        sides *= 10 + 2; // upper
    if(y2 != Y2)
        sides *= 10 + 4; // right
    if(x2 != X2)
        sides *= 10 + 3; // lower
    return sides;                   // side
}

#endif // MYLIB_HPP
