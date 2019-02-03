#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <cstdlib>       // rand, srand
#include <vector>

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

struct Retcs
{
	int x1, y1;
	int x2, y2;
}

vector<Rects> create(int w, int h)
{
	vector<Rects> rects;
	Rects r;
	r.x1 = 0;
	r.y1 = 0;
	r.x2 = w;
	r.y2 = h;
	rects.push_back(r);
	return rects;
}

void create_rects(int x, int y, int width, int length)
{	
	
}

#endif // MYLIB_HPP
