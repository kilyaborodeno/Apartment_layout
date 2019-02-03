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

	vector<int> count_rects_at_wall_x(vector<Rects>& rects)
	{
		vector<int> rects_at_wall;
		int w = 0;
		for(int i = 0; i < rects.size(); ++i)
			if(rects[i].x2 > w) 
				w = rects[i].x2;
		for(int i = 0; i < rects.size(); ++i){
			if(rects[i].x1 == 0 || rects[i].x2 == w)
				rects_at_wall.push_back(i);
		}
		return rects_at_wall;
	}

	vector<int> count_rects_at_wall_y(vector<Rects>& rects)
	{
		vector<int> rects_at_wall;
		int h = 0;
		for(int i = 0; i < rects.size(); ++i)
			if(rects[i].y2 > h) 
				h = rects[i].x2;
		for(int i = 0; i < rects.size(); ++i){
			if(rects[i].y1 == 0 || rects[i].y2 == w)
				rects_at_wall.push_back(i);
		}
		return rects_at_wall;
	}

	bool fits(Rect r)
	{
		if((x2 - x1 > width)&&(y2 - y1 > length))
			return true;
		return false;
	}

	void choose_rect(vector<Rects>& rects)
	{
		if(wall_x)
		{
			vector<int> rects_at_wall = count_rects_at_wall_x(rects);
			for(int i = 0; i < rects_at_wall.size(); ++i)
			{
				if(!rects[rects_at_wall[i]].fits) 
					rects_at_wall.erase(rects_at_wall.begin() + i);
			}
			int choise = rand()%rects_at_wall.size();
			current_rect = rect_at_wall[choise];
		}
		else if(wall_y)
		{

			vector<int> rects_at_wall = count_rects_at_wall_y(rects);
			for(int i = 0; i < rects_at_wall.size(); ++i)
			{
				if(!rects[rects_at_wall[i]].fits) 
					rects_at_wall.erase(rects_at_wall.begin() + i);
			}
			int choise = rand()%rects_at_wall.size();
			current_rect = rects_at_wall[choise];
		}
		else
		{
			int w = 0;
			for(int i = 0; i < rects.size(); ++i)
				if(rects[i].x2 > w) 
					w = rects[i].x2;
			int h = 0;
			for(int i = 0; i < rects.size(); ++i)
				if(rects[i].y2 > h) 
					h = rects[i].x2;
			vector<int> proper_rects;
			for(int i = 0; i < rects.size(); ++i)
			{
				if(rects[i].x1 == 0 || rects[i].y1 == 0 || rects[i].x2 == w || rects.y2 == h)
					continue;
				proper_rects.push_back(i);
			}
			int choice = rand()%proper_rects.size();
			current_rect = proper_rects[choise];
		}
		rects[current_rect].slice();
	//	current_rect = count_current_rect();
	}

	void gen_coords(int x1, int y1, int x2, int y2)
	{
		if(width > w) rotate();
		if(length > h) rotate();
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
