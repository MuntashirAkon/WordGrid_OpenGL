/**
 * OpenGL helper functions.
 *
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_GL_HELPERS
#define _H_GL_HELPERS

#ifdef __APPLE__
#include <OpenGL/gltypes.h>
#else
#include <GL/gltypes.h>
#endif

void drawBitmap(GLfloat x, GLfloat y, const char *filename);

void drawText(GLdouble x, GLdouble y, char *str, void *font = GLUT_BITMAP_8_BY_13);

void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

void drawFilledPolygon(GLfloat *x, GLfloat *y, int size);

void drawRectangle(GLfloat left, GLfloat bottom, GLfloat dx, GLfloat dy);

void drawFilledRectangle(GLfloat left, GLfloat bottom, GLfloat dx, double dy);

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat r, int slices = 100);

void drawCircle(GLfloat x, GLfloat y, GLfloat r, int slices = 100);

void setColor(double r, double g, double b);

void delay(int sec);

void clearDisplay();

#endif // _H_GL_HELPERS
