#include <iostream>      // cin, cout, ...
#include <fstream>       // ifstream, ostream
#include "mycanvas.hpp"  // graphics
#include "mylib.hpp"     // Some special functions
#include <ctime>         // time
#include <vector>        // vector

using namespace std;
using namespace cnv;

vector<Piece> furniture;
double SCALE;
int width, height;

void onPaint(void);
void reshape(int w, int h);
void tick(int);

int main()
{
    setlocale(LC_ALL, "rus");
	ifstream file("C:/Users/bav73/Работа с исходным кодом/Проект/First version/info.txt");
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

	for (int i = 0; i < furniture.size(); ++i)
		cout << furniture[i] << endl;

	const int max_pixels = 1000;
	const double max_len = max(furniture[0].length, furniture[0].width);
	SCALE = max_pixels / max_len;

	const int wid = SCALE*furniture[0].width;
	const int len = SCALE*furniture[0].length;

    width = max(wid, len);
    height = min(len, wid);

	srand(time(0));
	window(wid, len, "Apartment layout");
	glutDisplayFunc(onPaint);
	glutReshapeFunc(reshape);
	glutTimerFunc(1,tick,1);
	glutMainLoop();
}

void tick(int)
{
	glutPostRedisplay();
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
    clear(255,255,255);
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

void reshape (int w, int h)
{
  double scale = min(double(w)/width, double(h)/height);
  width *= scale;
  height *= scale;
  int x = max((w - width)/2, 0);
  int y = max((h - height)/2, 0);
  glViewport (x, y, width, height);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (0, width, height, 0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}
