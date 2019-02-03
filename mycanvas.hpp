#ifndef MYCANVAS_HPP
#define MYCANVAS_HPP

#include "glcanvas.hpp"
#include <cstdlib>       // rand, srand

void background(cnv::color_t c)
{
	cnv::rect_fill(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), c);
}

unsigned rand_color(int opacity)
{
	return cnv::hexcolor(rand()%256, rand()%256, rand()%256, opacity);
}

void draw_img(cnv::Image &img, int x, int y, double sz, bool opaque = 1)
{
	double cc[4];
	glGetDoublev(GL_CURRENT_COLOR, cc);

	if (opaque)
		cnv::color4(255, 255, 255);
	img.draw(x, y, sz);

	cnv::color4(cc[0]*255, cc[1]*255, cc[2]*255, cc[3]*255);
}
#endif // MYCANVAS_HPP
