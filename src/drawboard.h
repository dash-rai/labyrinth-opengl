#ifndef _DRAWBOARD_H
#define _DRAWBOARD_H

#define NUMBER_OF_WALLS 4
/*
 * X, Y, Z stand for the co-ordinates
 * T is the thickness of the wall
 * H is the height
 */
#define X 2.0
#define Y 2.0
#define Z 0.5
#define T 0.08
#define H 0.2

void drawBoard(GLuint texture);
void quad(int, int, int, int);

#endif /* _DRAWBOARD_H */
