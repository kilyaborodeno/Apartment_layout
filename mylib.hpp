#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <cstdlib>       // rand, srand
#include <iostream>

using namespace std;

class Piece
{
public:
	string name;
	double length;
	double width;
	double height;
	int count;
	bool wall_x;
	bool wall_y;

//	void rotate()
//	{
//
//	}
};

ostream& operator<<(ostream& out, const Piece& p)
{
	out << "name: " << p.name << endl;
	out << "length: " << p.length << endl;
	out << "width: " << p.width << endl;
	out << "height: " << p.height << endl;
	out << "count: " << p.count << endl;
	return out;
}

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

#endif // MYLIB_HPP
