#include <iostream>
#include "mycanvas.hpp"
#include <ctime>
using namespace std;
using namespace cnv;

int CIRCLE_X = 50, CIRCLE_Y = 50;

void tick(int)
{
	if (CIRCLE_X < 300)
		CIRCLE_X+=2;
	if (CIRCLE_Y < 300)
		CIRCLE_Y+=2;
	if (CIRCLE_X < 300 || CIRCLE_Y < 300)
		glutTimerFunc(10, tick, 0);
	glutPostRedisplay();
}

void onPaint()
{
	background(hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));
	rect_fill(0, 0, 600, 100, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));
	rect_fill(0, 100, 600, 200, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));
	rect_fill(0, 200, 600, 300, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));
	rect_fill(0, 300, 600, 400, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));
	rect_fill(0, 400, 600, 500, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));
	rect_fill(0, 500, 600, 600, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));
	color4(0, 0, 0);

	Image img("/home/new/bupe/p.png");
	draw_img(img, 250, 100, 0.16);

	position(150, 304);
	text_out << "BLACK";

	rect_fill(200, 280, 400, 320);
	circle_fill(CIRCLE_X, 300, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256)); // r g b a

	circle_fill(600-CIRCLE_X, 300, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));

	circle_fill(600-CIRCLE_X, CIRCLE_Y, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));

	circle_fill(CIRCLE_X, CIRCLE_Y, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));

	circle_fill(600-CIRCLE_X, 600-CIRCLE_Y, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));

	circle_fill(CIRCLE_X, 600-CIRCLE_Y, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));

	circle_fill(300, 0+CIRCLE_Y, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));

	circle_fill(300, 600-CIRCLE_Y, 50, hexcolor(rand() % 256, rand() % 256,  rand() % 256,  rand() % 256));

	circle(300, 300, 50, hexcolor(0, 255, 0));

	color4(255, 255, 255);
	position(278, 304);
	text_out << "Hello";
	glutSwapBuffers();
}

int main()
{
	srand(time(0));
	window(600, 600);
	glutDisplayFunc(onPaint);
	tick(0);
	glutMainLoop();
}
