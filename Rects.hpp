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

ostream& operator<<(ostream& out, const Rect r)
{
	out << "x1: " << r.x1 << endl;
	out << "y1: " << r.y1 << endl;
	out << "x2: " << r.x2 << endl;
	out << "y2: " << r.y2 << endl;
	out << "chosen: " << r.chosen << endl;
	return out;
}

class Rects{
public:
    vector<Rect> num; // an array of all rectangles (including room)

	vector<int> count_rects_at_wall_x()
	{
		vector<int> rects_at_wall;
		int w = 0;
		for(size_t i = 0; i < num.size(); ++i) // calculating the width of the room
			if(num[i].x2 > w)
				w = num[i].x2;
		for(size_t i = 0; i < num.size(); ++i) // calculating the number of rectangles leaning on wall_x
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
		for(size_t i = 0; i < num.size(); ++i) // calculating the length of the room
			if(num[i].y2 > len)
				len = num[i].x2;
		for(size_t i = 0; i < num.size(); ++i) // calculating the number of rectangles leaning on wall_y
        {
			if(num[i].y1 == 0 || num[i].y2 == len)
				rects_at_wall.push_back(i);
		}
		return rects_at_wall;
	}
/**
* 1 left
* 2 upper
* 3 right
* 4 lower
**/
	int slice(int X1, int Y1, int X2, int Y2, int number)
	{
	    // sizes of rectangle where object is drawn
        int x1 = num[number].x1;
        int y1 = num[number].y1;
        int x2 = num[number].x2;
        int y2 = num[number].y2;

		if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2) == 4)
			return number;

		int s = which_sides_free(x1, y1, x2, y2, X1, Y1, X2, Y2);
		if(num.size() != 1) num.erase(num.begin() + number);// deleting a sliced rectangle from an array

		if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2) == 3)
		{
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
			return num.size()-2;// returning new current rectangle number to make it chosen
		}

		if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2) == 2)
		{
			Rect r1, r2, r3, r4;
			r1.x1 = X1; r1.y1 = Y1; r1.x2 = X2; r1.y2 = Y2; // Calculating the coordinates of four new rectangles
			switch(s)
			{
				case 14: r2.x1 = x1; r2.y1 = Y2; r2.x2 = X2; r2.y2 = y2;
						 r3.x1 = X2; r3.y1 = Y2; r3.x2 = x2; r3.y2 = y2;
						 r4.x1 = X2; r4.y1 = Y1; r4.x2 = X2; r4.y2 = y2;
						 cout << r2.x1 << ' ' << r2.y1 << ' ' << r2.x2 << ' ' << r2.y2 << endl;
				break;
				case 34: r2.x1 = x1; r2.y1 = y1; r2.x2 = X1; r2.y2 = Y2;
						 r3.x1 = x1; r3.y1 = Y2; r3.x2 = X1; r3.y2 = y2;
						 r4.x1 = X1; r4.y1 = Y1; r4.x2 = x2; r4.y2 = y2;
						 cout << r2.x1 << ' ' << r2.y1 << ' ' << r2.x2 << ' ' << r2.y2 << endl;
				break;
				case 23: r2.x1 = x1; r2.y1 = Y1; r2.x2 = X1; r2.y2 = y2;
						 r3.x1 = x1; r3.y1 = y1; r3.x2 = X1; r3.y2 = Y1;
						 r4.x1 = X1; r4.y1 = y1; r4.x2 = x2; r4.y2 = Y1;
						 cout << r2.x1 << ' ' << r2.y1 << ' ' << r2.x2 << ' ' << r2.y2 << endl;
				break;
				case 12: r2.x1 = x1; r2.y1 = y1; r2.x2 = X2; r2.y2 = Y2;
						 r3.x1 = X2; r3.y1 = y1; r3.x2 = x2; r3.y2 = Y1;
						 r4.x1 = X2; r4.y1 = Y1; r4.x2 = x2; r4.y2 = y2;
						 cout << r2.x1 << ' ' << r2.y1 << ' ' << r2.x2 << ' ' << r2.y2 << endl;
				break;
			}
			num.push_back(r1);// adding four new rectangles to an array
			num.push_back(r2);
			num.push_back(r3);
			num.push_back(r4);
			cout << r1 << r2 << r3 << r4 << endl;
			return num.size()-4;// returning new current rectangle number to make a it chosen
		}

		if(sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2) == 1)
		{
			Rect r1, r2, r3, r4, r5, r6;
			r1.x1 = X1; r1.y1 = Y1; r1.x2 = X2; r1.y2 = Y2; // Calculating the coordinates of six new rectangles
			switch(s)
			{
				case 234: r2.x1 = x1; r2.y1 = y1; r2.x2 = X2; r2.y2 = Y1;
						  r3.x1 = X2; r3.y1 = y1; r3.x2 = x2; r3.y2 = Y1;
						  r4.x1 = X2; r4.y1 = Y1; r4.x2 = x2; r4.y2 = Y2;
						  r5.x1 = X2; r5.y1 = Y2; r5.x2 = x2; r5.y2 = y2;
						  r6.x1 = x1; r6.y1 = Y2; r6.x2 = X2; r6.y2 = y1;
				break;
				case 134: r2.x1 = x1; r2.y1 = y1; r2.x2 = X1; r2.y2 = Y2;
						  r3.x1 = x1; r3.y1 = Y2; r3.x2 = X1; r3.y2 = y2;
						  r4.x1 = X1; r4.y1 = Y2; r4.x2 = X2; r4.y2 = y2;
						  r5.x1 = X2; r5.y1 = Y2; r5.x2 = x2; r5.y2 = y2;
						  r6.x1 = X2; r6.y1 = y1; r6.x2 = x2; r6.y2 = Y2;
				break;
				case 124: r2.x1 = X1; r2.y1 = y1; r2.x2 = x2; r2.y2 = Y1;
						  r3.x1 = x1; r3.y1 = y1; r3.x2 = X1; r3.y2 = Y1;
						  r4.x1 = x1; r4.y1 = Y1; r4.x2 = X1; r4.y2 = Y2;
						  r5.x1 = x1; r5.y1 = Y2; r5.x2 = X1; r5.y2 = y2;
						  r6.x1 = X1; r6.y1 = Y2; r6.x2 = x2; r6.y2 = y2;
				break;
				case 123: r2.x1 = x1; r2.y1 = Y1; r2.x2 = X1; r2.y2 = y2;
						  r3.x1 = x1; r3.y1 = y1; r3.x2 = X1; r3.y2 = Y1;
						  r4.x1 = X1; r4.y1 = y1; r4.x2 = X2; r4.y2 = Y1;
						  r5.x1 = X2; r5.y1 = y1; r5.x2 = x2; r5.y2 = Y1;
						  r6.x1 = X2; r6.y1 = Y1; r6.x2 = x2; r6.y2 = y2;
				break;
			}
			num.push_back(r1);// adding six new rectangles to an array
			num.push_back(r2);
			num.push_back(r3);
			num.push_back(r4);
			num.push_back(r5);
			num.push_back(r6);
			return num.size()-6;// returning new current rectangle number to make it chosen
		}

		// sides_at_wall == 0
		Rect r1, r2, r3, r4, r5, r6, r7, r8, r9;
		r1.x1 = X1; r1.y1 = Y1; r1.x2 = X2; r1.y2 = Y2; // Calculating the coordinates of six new rectangles
		r2.x1 = x1; r2.y1 = y1; r2.x2 = X1; r2.y2 = Y1;
		r3.x1 = X1; r3.y1 = y1; r3.x2 = X2; r3.y2 = Y1;
		r4.x1 = X2; r4.y1 = y1; r4.x2 = x2; r4.y2 = Y1;
		r5.x1 = X2; r5.y1 = Y1; r5.x2 = x2; r5.y2 = Y2;
		r6.x1 = X2; r6.y1 = Y2; r6.x2 = x2; r6.y2 = y2;
		r7.x1 = X1; r7.y1 = Y2; r7.x2 = X2; r7.y2 = y2;
		r8.x1 = x1; r8.y1 = Y2; r8.x2 = X1; r8.y2 = y2;
		r9.x1 = x1; r9.y1 = Y1; r9.x2 = X1; r9.y2 = Y2;
		num.push_back(r1);// adding nine new rectangles to an array
		num.push_back(r2);
		num.push_back(r3);
		num.push_back(r4);
		num.push_back(r5);
		num.push_back(r6);
		num.push_back(r7);
		num.push_back(r8);
		num.push_back(r9);
		return num.size()-9;// returning new current rectangle number to make it chosen
	}

	bool merge()
	{
	    bool found = false;
        for(size_t i = 0; i < num.size(); ++i)
        {
            if(!num[i].chosen)
            {
                for(size_t k = 0; k < num.size(); ++k) // Searching for rectangles near rectangle number i
                {
                    if(i == k)
                        continue;
                    if(((num[i].x1 == num[k].x1 && num[i].y1 == num[k].y1)&& // if left side is the same, merge two rectangles
                    (num[i].x1 == num[k].x1 && num[i].y2 == num[k].y2))||
                    ((num[i].x1 == num[k].x1 && num[i].y1 == num[k].y1)&& // if upper side is the same, merge two rectangles
                    (num[i].x2 == num[k].x2 && num[i].y1 == num[k].y1)))
                    {
                        Rect n; // new
                        n.x1 = num[k].x1;
                        n.y1 = num[k].y1;
                        n.x2 = num[i].x2;
                        n.y2 = num[i].y2;
                        if(i) num.erase(num.begin() + i);
						if(k > i) k--;
                        if(k) num.erase(num.begin() + k);
                        num.push_back(n);
                        found = true;
                        break;
                    }
                    if (((num[i].x2 == num[k].x2 && num[i].y1 == num[k].y1)&& // if right side is the same, merge two rectangles
                    (num[i].x2 == num[k].x2 && num[i].y2 == num[k].y2))||
                    ((num[i].x1 == num[k].x1 && num[i].y2 == num[k].y2)&& // if lower side is the same, merge two rectangles
                    (num[i].x2 == num[k].x2 && num[i].y2 == num[k].y2)))
                    {
                        Rect n; // new
                        n.x1 = num[i].x1;
                        n.y1 = num[i].y1;
                        n.x2 = num[k].x2;
                        n.y2 = num[k].y2;
                        if(i) num.erase(num.begin() + i);
						if(k > i) k--;
                        if(k) num.erase(num.begin() + k);
                        num.push_back(n);
                        found = true;
                        break;
                    }
                }
                if(found)
                    break;
            }
        }
        if(found)
            return true;
        return false;
	}

	void merge_all()
	{
	    bool goes = false;
        do
        {
            goes = merge();
        }while(goes);
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
