#include <iostream>      // cin, cout, ...
#include <fstream>       // ifstream, ostream
#include "mycanvas.hpp"  // graphics
#include <ctime>         // time
#include <vector>        // vector
using namespace std;
using namespace cnv;

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

vector<Piece> furniture;
double SCALE;

double max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

ostream& operator<<(ostream& out, const Piece& p)
{
	out << "name: " << p.name << endl;
	out << "length: " << p.length << endl;
	out << "width: " << p.width << endl;
	out << "height: " << p.height << endl;
	out << "count: " << p.count << endl;
	return out;
}

void tick(int)
{
	glutPostRedisplay();
}

int pick_of_two(int a, int b)
{
	bool r = rand() % 2;
	return a*r + b*(!r);
}

int get_x(Piece p)
{
	if(p.wall_x)
		return pick_of_two(0, glutGet(GLUT_WINDOW_WIDTH) - SCALE*p.width);

	return rand()%int(glutGet(GLUT_WINDOW_WIDTH) - SCALE*p.width);
}

int get_y(Piece p)
{
	if(p.wall_y)
		return pick_of_two(0, glutGet(GLUT_WINDOW_HEIGHT) - SCALE*p.length);
	return rand()%int(glutGet(GLUT_WINDOW_HEIGHT) - SCALE*p.length);
}

void onPaint()
{
	for (int i = 1; i < furniture.size(); ++i)
		for (int j = 0; j < furniture[i].count; ++j)
		{
			int left_x = get_x(furniture[i]);
			int top_y = get_y(furniture[i]);
			int right_x = left_x + SCALE*furniture[i].width;
			int bottom_y = top_y + SCALE*furniture[i].length;

			rect_fill(left_x, top_y, right_x, bottom_y, rand_color(150));
		}

	glutSwapBuffers();
}

int main()
{
	ifstream file("info.txt");
	string s;
	while (file >> s)
	{
		if (s[0] == '#')
			getline(file, s);
		else
		{
			Piece p;
			p.name = s;
			file >> p.length;
			file >> p.width;
			file >> p.height;
			file >> p.count;
			file >> p.wall_x;
			file >> p.wall_y;
			furniture.push_back(p);
		}
	}

	for (int i; i < furniture.size(); ++i)
		cout << furniture[i] << endl;
	
	const int max_pixels = 1000;
	const double max_len = max(furniture[0].length, furniture[0].width);
	SCALE = max_pixels / max_len;

	const int width = SCALE*furniture[0].width;
	const int length = SCALE*furniture[0].length;

	srand(time(0));
	window(width, length);
	glutDisplayFunc(onPaint);
	tick(0);
	glutMainLoop();
}
