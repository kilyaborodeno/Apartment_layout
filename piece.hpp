#ifndef PIECE_HPP
#define PIECE_HPP

#include<iostream>
#include"mylib.hpp"
using namespace std;

class Piece
{
public:
	string name;
	bool wall_x, wall_y;
	int length, width, height;
	int x, y;
	cnv::color_t color;

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

	void gen_coords(int w, int h)
	{
		rotate_to_wall();
		int free_w = w - width;
		int free_h = h - length;
		if(wall_x)
			x = pick_of_two(0, free_w);
		else if(free_w)
			x = rand()%free_w;
		if(wall_y)
			y = pick_of_two(0, free_h);
		else if(free_h)
			y = rand()%free_h;
		color = rand_color(150);
	}

	void rotate() // todo
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
	return out;
}
#endif // PIECE_HPP
