#ifndef MYCANVAS_HPP
#define MYCANVAS_HPP

#include "glcanvas.hpp"

void background(cnv::color_t c)
{
	cnv::rect_fill(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), c);
}

void draw_img(cnv::Image &img, int x, int y, float sz, bool opaque = 1)
{
	float cc[4];
	glGetFloatv(GL_CURRENT_COLOR, cc);

	if (opaque)
		cnv::color4(255, 255, 255);
	img.draw(x, y, sz);

	cnv::color4(cc[0]*255, cc[1]*255, cc[2]*255, cc[3]*255);
}
#endif // MYCANVAS_HPP
