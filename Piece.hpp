#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include "mylib.hpp"
#include "Rects.hpp"
using namespace std;

class Piece
{
public:
	string name;
	bool wall_x, wall_y;
	int length, width, height;
	int x, y;
	int current_rect = 0;
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

	void choose_rect(Rects rects)
	{
		if(wall_x)
		{
			vector<int> rects_at_wall = rects.count_rects_at_wall_x(); // all rectangle numbers at wall_x
			for(int i = 0; i < rects_at_wall.size(); ++i) // deleting inappropriate rectangle numbers
			{
				if(!rects.num[rects_at_wall[i]].fits(width, length) || rects.num[rects_at_wall[i]].chosen == true)
					rects_at_wall.erase(rects_at_wall.begin() + i);
			}
			if(rects_at_wall.size()) // choosing one of proper rectangles
            {
                int choise = rand()%rects_at_wall.size();
                current_rect = rects_at_wall[choise];
            }
            else
                current_rect = 0; // if no proper rectangle choose the whole room
		}
		else if(wall_y)
		{
			vector<int> rects_at_wall = rects.count_rects_at_wall_y();// all rectangle numbers at wall_y
			for(size_t i = 0; i < rects_at_wall.size(); ++i) // deleting inappropriate rectangle numbers
			{
				if(!rects.num[rects_at_wall[i]].fits(width, length) || rects.num[rects_at_wall[i]].chosen == true)
					rects_at_wall.erase(rects_at_wall.begin() + i);
			}
			if(rects_at_wall.size()) // choosing one of proper rectangles
            {
                int choise = rand()%rects_at_wall.size();
                current_rect = rects_at_wall[choise];
            }
            else
                current_rect = 0; // if no proper rectangle choose the whole room
		}
		else
		{
			int w = 0;
			for(size_t i = 0; i < rects.num.size(); ++i) // calculating the width of the room
				if(rects.num[i].x2 > w)
					w = rects.num[i].x2;
			int l = 0;
			for(size_t i = 0; i < rects.num.size(); ++i) // calculating the length of the room
				if(rects.num[i].y2 > l)
					l = rects.num[i].x2;
			vector<int> proper_rects;
			for(size_t i = 0; i < rects.num.size(); ++i) // creating an array with proper rectangles
			{
				if(rects.num[i].x1 == 0 || rects.num[i].y1 == 0 ||
                   rects.num[i].x2 == w || rects.num[i].y2 == l || rects.num[i].chosen == true)
					continue;
				proper_rects.push_back(i);
			}
			if(proper_rects.size()) // choosing one of proper rectangles
            {
                int choise = rand()%proper_rects.size();
                current_rect = proper_rects[choise];
            }
            else
                current_rect = 0; // if no proper rectangle choose the whole room
		}
	}

    // when generating coordinates the rectangle always fits the room
	void gen_coords(Rect r)
	{
        rotate_to_wall();
		if(wall_y && width > r.x2 - r.x1) rotate(); // rotating the object to fit in by width and length
		if(wall_x && length > r.y2 - r.y1) rotate();

		int free_w = r.x2 - r.x1 - width; // calculating the coordinates range
		int free_h = r.y2 - r.y1 - length;
		if(wall_x)
			x = r.x1 + pick_of_two/*walls*/(0, free_w);
		else if(free_w)
			x = r.x1 + rand()%free_w;
			else x = r.x1 + 0;
		if(wall_y)
			y = r.y1 + pick_of_two/*walls*/(0, free_h);
		else if(free_h)
			y = r.y1 + rand()%free_h;
			else y = r.y1 + 0;
		color = rand_color(150);
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
	return out;
}
#endif // PIECE_HPP
