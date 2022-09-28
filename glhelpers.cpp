/**
 * OpenGL helper functions.
 *
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifdef __WINDOWS__
#include <windows.h>
#else
#include "bmpreader.h"
#endif

#include "glhelpers.h"

void drawBitmap(GLfloat x, GLfloat y, const char *filename)
{
	AUX_RGBImageRec *img = auxDIBImageLoad(filename);

	glRasterPos2f(x, y);
	glDrawPixels(img->sizeX, img->sizeY, GL_RGB, GL_UNSIGNED_BYTE, img->data);

	free(img->data);
	free(img);
}

void drawText(GLdouble x, GLdouble y, char *str, void *font)
{
	glRasterPos3d(x, y, 0);
	int i;
	for (i = 0; str[i]; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void drawFilledPolygon(GLfloat *x, GLfloat *y, int size)
{
	int i;
	if (size < 3)
	{
		return;
	}
	glBegin(GL_POLYGON);
	for (i = 0; i < size; i++)
	{
		glVertex2f(x[i], y[i]);
	}
	glEnd();
}

void drawRectangle(GLfloat left, GLfloat bottom, GLfloat dx, GLfloat dy)
{
	GLfloat x1, y1, x2, y2;

	x1 = left;
	y1 = bottom;
	x2 = x1 + dx;
	y2 = y1 + dy;

	drawLine(x1, y1, x2, y1);
	drawLine(x2, y1, x2, y2);
	drawLine(x2, y2, x1, y2);
	drawLine(x1, y2, x1, y1);
}

void drawFilledRectangle(GLfloat left, GLfloat bottom, GLfloat dx, double dy)
{
	GLfloat xx[4], yy[4];
	GLfloat x1, y1, x2, y2;

	x1 = left;
	y1 = bottom;
	x2 = x1 + dx;
	y2 = y1 + dy;

	xx[0] = x1;
	yy[0] = y1;
	xx[1] = x2;
	yy[1] = y1;
	xx[2] = x2;
	yy[2] = y2;
	xx[3] = x1;
	yy[3] = y2;

	drawFilledPolygon(xx, yy, 4);
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat r, int slices)
{
	double t, PI = acos(-1), dt, x1, y1, xp, yp;
	dt = 2 * PI / slices;
	xp = x + r;
	yp = y;
	glBegin(GL_POLYGON);
	for (t = 0; t <= 2 * PI; t += dt)
	{
		x1 = x + r * cos(t);
		y1 = y + r * sin(t);

		glVertex2f(xp, yp);
		xp = x1;
		yp = y1;
	}
	glEnd();
}

void drawCircle(GLfloat x, GLfloat y, GLfloat r, int slices)
{
	double t, PI = acos(-1), dt, x1, y1, xp, yp;
	dt = 2 * PI / slices;
	xp = x + r;
	yp = y;
	for (t = 0; t <= 2 * PI; t += dt)
	{
		x1 = x + r * cos(t);
		y1 = y + r * sin(t);
		drawLine(xp, yp, x1, y1);
		xp = x1;
		yp = y1;
	}
}

void setColor(double r, double g, double b)
{
	double mmx;
	mmx = r;
	if (g > mmx)
		mmx = g;
	if (b > mmx)
		mmx = b;
	mmx = 255;
	if (mmx > 0)
	{
		r /= mmx;
		g /= mmx;
		b /= mmx;
	}
	glColor3f(r, g, b);
}

void delay(int sec)
{
	int t1, t2;
	t1 = time(0);
	while (1)
	{
		t2 = time(0);
		if (t2 - t1 >= sec)
			break;
	}
}

void clearDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0, 0, 0, 0);
	glFlush();
}
