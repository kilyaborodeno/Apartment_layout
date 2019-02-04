#ifndef RECTS_HPP
#define RECTS_HPP

#include <vector>
#include <cstdlib>

using namespace std;

struct Rect
{
	int x1, y1;
	int x2, y2;
	bool chosen; // if the rectangle is taken

	bool fits(int width, int length)
	{
		if((x2 - x1 < width)||(y2 - y1 < width)) // also checking if the object can be rotated and fit in rectangle
            if((x2 - x1 < length)||(y2 - y1 < length))
                return true;
		return false;
	}
};

class Rects{
public:
    vector<Rect> num; // an array all rectangles (including room)

	vector<int> count_rects_at_wall_x()
	{
		vector<int> rects_at_wall;
		int w = 0;
		for(int i = 0; i < num.size(); ++i) // calculating the width of the room
			if(num[i].x2 > w)
				w = num[i].x2;
		for(int i = 0; i < num.size(); ++i) // calculating the number of rectangles leaning on wall_x
        {
			if(num[i].x1 == 0 || num[i].x2 == w)
				rects_at_wall.push_back(i);
		}
		return rects_at_wall;
	}

	vector<int> count_rects_at_wall_y()
	{
		vector<int> rects_at_wall;
		int len = 0;
		for(int i = 0; i < num.size(); ++i) // calculating the length of the room
			if(num[i].y2 > len)
				len = num[i].x2;
		for(int i = 0; i < num.size(); ++i) // calculating the number of rectangles leaning on wall_y
        {
			if(num[i].y1 == 0 || num[i].y2 == len)
				rects_at_wall.push_back(i);
		}
		return rects_at_wall;
	}

/*
* x1 == x
* y1 == y
* x2 == x+width
* y2 == y+length
* x1 == x && y1 == y
* x1 == x && y2 == y+length
* x2 == x+width && y1 == y
* x2 == x+width && y2 == y+length
* x1 == x && y1 == y && x2 == x+width && y2 == y+length
*
* 1 left
* 2 upper
* 3 right
* 4 lower
*/

	int slice(int X1, int Y1, int X2, int Y2, int number)
	{
	    // sizes of rectangle where object is drawn
        int x1 = num[number].x1;
        int y1 = num[number].y1;
        int x2 = num[number].x2;
        int y2 = num[number].y2;

        if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2))
        {
            if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2) == 4)
                return number;
            if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2) == 3)
            {
                num.erase(num.begin() + number);// deleting a sliced rectangle from an array
                int s = which_sides_free(x1, y1, x2, y2, X1, Y1, X2, Y2);
                Rect r1, r2;
                r1.x1 = X1; r1.y1 = Y1; r1.x2 = X2; r1.y2 = Y2; // Calculating the coordinates of two new rectangles
                switch(s)
                {
                    case 1: r2.x1 = x1; r2.y1 = y1; r2.x2 = X1; r2.y2 = y2; break;
                    case 2: r2.x1 = x1; r2.y1 = y1; r2.x2 = x2; r2.y2 = Y1; break;
                    case 3: r2.x1 = X1; r2.y1 = y1; r2.x2 = x2; r2.y2 = y2; break;
                    case 4: r2.x1 = x1; r2.y1 = Y1; r2.x2 = X1; r2.y2 = y2; break;
                }
                num.push_back(r1);// adding two new rectangles to an array
                num.push_back(r2);
                return num.size()-2;// returning new current rectangle number to make a new rectangle chosen
            }
            /********
            * @TODO *
            ********/
            if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2) == 2);
        }


	}

	void merge()
	{
        for(int i = 0; i < num.size(); ++i)
        {
            if(!num[i].chosen);
        }
	}

};

Rects create(int w, int h)
{
	Rects rects;
    Rect r;
    r.x1 = 0;
    r.y1 = 0;
    r.x2 = w;
    r.y2 = h;
    rects.num.push_back(r);
	return rects;
}

#endif // RECTS_HPP
