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

	Rect()
	{
	    chosen = false;
	}

	bool fits(int width, int length)
	{
		if(((x2 - x1 >= width) && (y2 - y1 >= length)) || ((x2 - x1 >= length) && (y2 - y1 >= width)))
                return true;
		return false;
	}
};

ostream& operator<<(ostream& out, const Rect r)
{
	out << "\tx1: " << r.x1 << endl;
	out << "\ty1: " << r.y1 << endl;
	out << "\tx2: " << r.x2 << endl;
	out << "\ty2: " << r.y2 << endl;
	out << "\tchosen: " << std::string(r.chosen ? "true" : "false") << endl;
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

        int sides = sides_at_wall(x1, y1, x2, y2, X1, Y1, X2, Y2);

		if(sides == 4)
			return number;

		int s = which_sides(x1, y1, x2, y2, X1, Y1, X2, Y2);
		num.erase(num.begin() + number);// deleting a sliced rectangle from an array

		if(sides == 3)
		{
			Rect r[2];
			r[0].x1 = X1; r[0].y1 = Y1; r[0].x2 = X2; r[0].y2 = Y2; r[0].chosen = true; // Calculating the coordinates of two new rectangles
			switch(s)
			{
				case 123: r[1].x1 = x1; r[1].y1 = Y2; r[1].x2 = x2; r[1].y2 = y2; break;
				case 234: r[1].x1 = x1; r[1].y1 = y1; r[1].x2 = X1; r[1].y2 = y2; break;
				case 134: r[1].x1 = x1; r[1].y1 = y1; r[1].x2 = x2; r[1].y2 = Y1; break;
				case 124: r[1].x1 = X2; r[1].y1 = y1; r[1].x2 = x2; r[1].y2 = y2; break;
			}
			for(size_t i = 0; i < 2; ++i)   // adding two new rectangles to an array
                num.push_back(r[i]);
			return num.size()-2;    // returning new current rectangle number to make it chosen
		}

		if(sides == 2)
		{
			Rect r[4];
			r[0].x1 = X1; r[0].y1 = Y1; r[0].x2 = X2; r[0].y2 = Y2; r[0].chosen = true; // Calculating the coordinates of four new rectangles
			switch(s)
			{
				case 12: r[1].x1 = x1; r[1].y1 = Y2; r[1].x2 = X2; r[1].y2 = y2;
						 r[2].x1 = X2; r[2].y1 = Y2; r[2].x2 = x2; r[2].y2 = y2;
						 r[3].x1 = X2; r[3].y1 = y1; r[3].x2 = x2; r[3].y2 = Y2;
				break;
				case 23: r[1].x1 = x1; r[1].y1 = y1; r[1].x2 = X1; r[1].y2 = Y2;
						 r[2].x1 = x1; r[2].y1 = Y2; r[2].x2 = X1; r[2].y2 = y2;
						 r[3].x1 = X1; r[3].y1 = Y2; r[3].x2 = x2; r[3].y2 = y2;
				break;
				case 34: r[1].x1 = x1; r[1].y1 = Y1; r[1].x2 = X1; r[1].y2 = y2;
						 r[2].x1 = x1; r[2].y1 = y1; r[2].x2 = X1; r[2].y2 = Y1;
						 r[3].x1 = X1; r[3].y1 = y1; r[3].x2 = x2; r[3].y2 = Y1;
				break;
				case 14: r[1].x1 = x1; r[1].y1 = y1; r[1].x2 = X2; r[1].y2 = Y1;
						 r[2].x1 = X2; r[2].y1 = y1; r[2].x2 = x2; r[2].y2 = Y1;
						 r[3].x1 = X2; r[3].y1 = Y1; r[3].x2 = x2; r[3].y2 = y2;
				break;
			}
			for(size_t i = 0; i < 4; ++i)// adding four new rectangles to an array
                num.push_back(r[i]);
			return num.size()-4;// returning new current rectangle number to make a it chosen
		}

		if(sides == 1)
		{
			Rect r[6];
			r[0].x1 = X1; r[0].y1 = Y1; r[0].x2 = X2; r[0].y2 = Y2; r[0].chosen = true; // Calculating the coordinates of six new rectangles
			switch(s)
			{
				case 1: r[1].x1 = x1; r[1].y1 = y1; r[1].x2 = X2; r[1].y2 = Y1;
						r[2].x1 = X2; r[2].y1 = y1; r[2].x2 = x2; r[2].y2 = Y1;
						r[3].x1 = X2; r[3].y1 = Y1; r[3].x2 = x2; r[3].y2 = Y2;
						r[4].x1 = X2; r[4].y1 = Y2; r[4].x2 = x2; r[4].y2 = y2;
						r[5].x1 = x1; r[5].y1 = Y2; r[5].x2 = X2; r[5].y2 = y2;
				break;
				case 2: r[1].x1 = x1; r[1].y1 = y1; r[1].x2 = X1; r[1].y2 = Y2;
						r[2].x1 = x1; r[2].y1 = Y2; r[2].x2 = X1; r[2].y2 = y2;
						r[3].x1 = X1; r[3].y1 = Y2; r[3].x2 = X2; r[3].y2 = y2;
						r[4].x1 = X2; r[4].y1 = Y2; r[4].x2 = x2; r[4].y2 = y2;
						r[5].x1 = X2; r[5].y1 = y1; r[5].x2 = x2; r[5].y2 = Y2;
				break;
				case 3: r[1].x1 = X1; r[1].y1 = y1; r[1].x2 = x2; r[1].y2 = Y1;
						r[2].x1 = x1; r[2].y1 = y1; r[2].x2 = X1; r[2].y2 = Y1;
						r[3].x1 = x1; r[3].y1 = Y1; r[3].x2 = X1; r[3].y2 = Y2;
						r[4].x1 = x1; r[4].y1 = Y2; r[4].x2 = X1; r[4].y2 = y2;
						r[5].x1 = X1; r[5].y1 = Y2; r[5].x2 = x2; r[5].y2 = y2;
				break;
				case 4: r[1].x1 = x1; r[1].y1 = Y1; r[1].x2 = X1; r[1].y2 = y2;
						r[2].x1 = x1; r[2].y1 = y1; r[2].x2 = X1; r[2].y2 = Y1;
						r[3].x1 = X1; r[3].y1 = y1; r[3].x2 = X2; r[3].y2 = Y1;
						r[4].x1 = X2; r[4].y1 = y1; r[4].x2 = x2; r[4].y2 = Y1;
						r[5].x1 = X2; r[5].y1 = Y1; r[5].x2 = x1; r[5].y2 = y1;
				break;
			}
			for(size_t i = 0; i < 6; ++i) // adding six new rectangles to an array
                num.push_back(r[i]);
			return num.size()-6;// returning new current rectangle number to make it chosen
		}

		// sides == 0
		Rect r[9];
		r[0].x1 = X1; r[0].y1 = Y1; r[0].x2 = X2; r[0].y2 = Y2; r[0].chosen = true; // Calculating the coordinates of nine new rectangles
		r[1].x1 = x1; r[1].y1 = y1; r[1].x2 = X1; r[1].y2 = Y1;
		r[2].x1 = X1; r[2].y1 = y1; r[2].x2 = X2; r[2].y2 = Y1;
		r[3].x1 = X2; r[3].y1 = y1; r[3].x2 = x2; r[3].y2 = Y1;
		r[4].x1 = X2; r[4].y1 = Y1; r[4].x2 = x2; r[4].y2 = Y2;
		r[5].x1 = X2; r[5].y1 = Y2; r[5].x2 = x2; r[5].y2 = y2;
		r[6].x1 = X1; r[6].y1 = Y2; r[6].x2 = X2; r[6].y2 = y2;
		r[7].x1 = x1; r[7].y1 = Y2; r[7].x2 = X1; r[7].y2 = y2;
		r[8].x1 = x1; r[8].y1 = Y1; r[8].x2 = X1; r[8].y2 = Y2;
		for(size_t i = 0; i < 9; ++i)
            num.push_back(r[i]);// adding nine new rectangles to an array
		return num.size()-9;// returning new current rectangle number to make it chosen
	}

	bool merge()
	{
	    bool found = false;
        for(size_t i = 1; i < num.size(); ++i)
        {
            if(!num[i].chosen)
            {
                for(size_t k = 1; k < num.size(); ++k) // Searching for rectangles near rectangle number i
                {
                    if(i == k || num[k].chosen)
                        continue;
                    if(((num[i].x1 == num[k].x2 && num[i].y1 == num[k].y1)&& // if left side is the same, merge two rectangles
                    (num[i].x1 == num[k].x2 && num[i].y2 == num[k].y2))||
                    ((num[i].x1 == num[k].x1 && num[i].y1 == num[k].y2)&& // if upper side is the same, merge two rectangles
                    (num[i].x2 == num[k].x2 && num[i].y1 == num[k].y2)))
                    {
						unite(i, k, 1);
                    }
                    if(((num[i].x2 == num[k].x1 && num[i].y1 == num[k].y1)&& // if right side is the same, merge two rectangles
                    (num[i].x2 == num[k].x1 && num[i].y2 == num[k].y2))||
                    ((num[i].x1 == num[k].x1 && num[i].y2 == num[k].y1)&& // if lower side is the same, merge two rectangles
                    (num[i].x2 == num[k].x2 && num[i].y2 == num[k].y1)))
                    {
                        unite(i, k, 2)
                    }
                }
            }
			if(found)
				break;
        }
		return found;
	}

	void merge_all()
	{
	    bool goes = false;
        do
        {
            goes = merge();
        }while(goes);
	}
private:
    void unite(int i, int k, int case)
    {
        if(case == 1)
        {
            Rect n; // new
            n.x1 = num[k].x1;
            n.y1 = num[k].y1;
            n.x2 = num[i].x2;
            n.y2 = num[i].y2;
        }
        if(case == 2)
        {
            Rect n; // new
            n.x1 = num[i].x1;
            n.y1 = num[i].y1;
            n.x2 = num[k].x2;
            n.y2 = num[k].y2;
        }
        num.erase(num.begin() + i);
        if(k > i) k--;
        num.erase(num.begin() + k);
        num.push_back(n);
        found = true;
        break;
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
