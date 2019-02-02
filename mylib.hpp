#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <cstdlib>       // rand, srand
#include <iostream>

using namespace std;

int pick_of_two(int a, int b)
{
	bool r = rand() % 2;
	return a*r + b*(!r);
}

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

	// The piece of furniture leans on wall with the biggest side
	void rotate_to_wall()
	{
	    if(!(wall_x || wall_y))
            return;
	    if(wall_x)
        {
            if(width > length)
                swap(width, length);
        }
        if(wall_y)
        {
            if(width < length)
                swap(width, length);
        }
	}

	void rotate()
	{
        if(wall_x || wall_y)
        {
            swap(wall_x, wall_y);
            swap(width, length);
        }
	}
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

double max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

#endif // MYLIB_HPP
