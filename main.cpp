#include <iostream>      // cin, cout, ...
#include <fstream>       // ifstream, ostream
#include "mycanvas.hpp"  // graphics
#include "piece.hpp"  // graphics
#include "mylib.hpp"     // Some special functions
#include <ctime>         // time
#include <vector>        // vector

using namespace std;
using namespace cnv;

vector<Piece> furniture;
double SCALE;
double WIDTH, HEIGHT;

void onPaint(void);
void reshape(int w, int h);
void tick(int);
void load();

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
	load();

	window(WIDTH, HEIGHT);
	glutSetWindowTitle("Apartment layout");
	glutDisplayFunc(onPaint);
	glutReshapeFunc(reshape);
	glutTimerFunc(1,tick,1);
	glutMainLoop();
}

void load()
{
	ifstream file("info.txt");
	string s;
	while(file >> s)
	{
		if (s[0] == '#')
			getline(file, s);
		else
		{
			Piece p;
			p.name = s;
			int count;
			file >> p.length;
			file >> p.width;
			file >> p.height;
			file >> count;
			file >> p.wall_x;
			file >> p.wall_y;
			cout << p << endl;
			if (!furniture.size())
			{
				const int max_pixels = 1000;
				const double max_len = max(p.length, p.width);
				SCALE = max_pixels / max_len;
				WIDTH = SCALE*p.width;
				HEIGHT = SCALE*p.length;
				furniture.push_back(p);
			}
			else if ((p.length > furniture[0].length && p.length > furniture[0].width) ||
				   	(p.width > furniture[0].width && p.width > furniture[0].length) ||
				   	p.height > furniture[0].height)
				cout << "Предмет слишком большой" << endl;
			else
				for (int i = 0; i < count; ++i)
				{
					p.gen_coords(WIDTH/SCALE, HEIGHT/SCALE);
					furniture.push_back(p);
				}
		}
	}
}

void tick(int)
{
	glutPostRedisplay();
}

void onPaint()
{
    clear(255,255,255);
	glLineWidth(3);
	rect(0, 0, WIDTH, HEIGHT);
	for (int i = 1; i < furniture.size(); ++i)
		rect_fill(furniture[i].x*SCALE, furniture[i].y*SCALE,
                  furniture[i].x*SCALE+furniture[i].width*SCALE,
				  furniture[i].y*SCALE+furniture[i].length*SCALE,
				  furniture[i].color);

	glutSwapBuffers();
}

void reshape (int w, int h)
{
  double scale = min(double(w)/WIDTH, double(h)/HEIGHT);
  WIDTH *= scale;
  HEIGHT *= scale;
  SCALE *= scale;
  int x = max((w - WIDTH)/2, 0);
  int y = max((h - HEIGHT)/2, 0);
  glViewport (x, y, WIDTH, HEIGHT);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (0, WIDTH, HEIGHT, 0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}
