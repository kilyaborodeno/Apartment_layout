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

int sides_at_wall(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
    int sides = 0;
    if(x1 == X1)
        sides++; // left
    if(y1 == Y1)
        sides++; // upper
    if(x2 == X2)
        sides++; // right
    if(y2 == Y2)
        sides++; // lower
    return sides;         // side
}

int which_sides(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
	cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << X1 << ' ' << Y1 << ' ' << X2 << ' ' << Y2 << endl;
    int sides = 0;
    if(x1 == X1)
        sides = sides * 10 + 1; // left
    if(y1 == Y1)
        sides = sides * 10 + 2; // upper
    if(x2 == X2)
        sides = sides * 10 + 3; // right
    if(y2 == Y2)
        sides = sides * 10 + 4; // lower
	cout << sides << endl;
    return sides;                   // side
}

#endif // MYLIB_HPP
