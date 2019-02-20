#include <iostream>      // cin, cout, ...
#include <fstream>       // ifstream, ostream
#include "mycanvas.hpp"  // graphics
#include "Piece.hpp"     // room objects
#include "mylib.hpp"     // Some special functions
#include <ctime>         // time
#include <vector>        // vector

using namespace std;
using namespace cnv;

vector<Piece> furniture;
Rects rects;
double SCALE;
double WIDTH, HEIGHT;

void onPaint(void);
void reshape(int w, int h);
void tick(int);
void load();
void keyboard(unsigned char key, int mx, int my);
void place_objects();

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
	load();
	rects = create(WIDTH/SCALE, HEIGHT/SCALE);
	place_objects();

	window(WIDTH, HEIGHT);
	glutSetWindowTitle("Apartment layout");
	glutDisplayFunc(onPaint);
	glutReshapeFunc(reshape);
	glutTimerFunc(1,tick,1);
	glutKeyboardFunc(keyboard);
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
			//cout << p << endl;
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
					furniture.push_back(p);
				}
		}
	}
}

void place_objects()
{
    for(size_t i = 1; i < furniture.size(); ++i)
    {
        furniture[i].choose_rect(rects);
        if(furniture[i].current_rect == -1)
		   continue;	
		furniture[i].gen_coords(rects.num[furniture[i].current_rect]); // Generate coordinates in chosen rectangle
        int x1 = furniture[i].x;
        int y1 = furniture[i].y;
        int x2 = x1+furniture[i].width;
        int y2 = y1+furniture[i].length;
        furniture[i].current_rect = rects.slice(x1, y1, x2, y2, furniture[i].current_rect);
        rects.merge_all();
		/*
		for (size_t j = 0; j < rects.num.size(); ++j)
			cout << rects.num[j] << endl;
		*/
    }
	cout << "\t" << rects.num.size();
}

void tick(int)
{
	glutPostRedisplay();
}

void onPaint()
{
    clear(0,0,0);
	rect_fill(0, 0, WIDTH, HEIGHT, hexcolor(255,255,255));
	int i;
	for(i = 1; i < furniture.size(); ++i)
		if (furniture[i].placed)
			rect_fill(furniture[i].x*SCALE, furniture[i].y*SCALE,
					  furniture[i].x*SCALE+furniture[i].width*SCALE,
					  furniture[i].y*SCALE+furniture[i].length*SCALE,
					  furniture[i].color);

	for (int i = 0; i < rects.num.size(); ++i)
	{
		int x1 = rects.num[i].x1*SCALE;
		int x2 = rects.num[i].x2*SCALE;
		int y1 = rects.num[i].y1*SCALE;
		int y2 = rects.num[i].y2*SCALE;

		line(x1, y1, x1, y2);
		line(x2, y1, x2, y2);
		line(x1, y1, x2, y1);
		line(x1, y2, x2, y2);
	}
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

void keyboard(unsigned char key, int mx, int my)
{
	if(key == 27)
		exit(0);
	if(key == 'r' || key == 'R')
		place_objects();
	glutPostRedisplay();
}
