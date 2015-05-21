#ifndef _DRAWBOARD_H
#define _DRAWBOARD_H

#define NUMBER_OF_WALLS 4
/*
 * X, Y, Z stand for the co-ordinates
 * T is the thickness of the wall
 * H is the height
 */
#define X 3.0
#define Y 2.0
#define Z 0.5
#define T 0.08
#define H 0.2
#define INIT_WINDOW_WIDTH 1024
#define INIT_WINDOW_HEIGHT 768
#define BALL_RADIUS 0.075
/* MUST be greater than BALL_RADIUS */
#define HOLE_RADIUS 0.08

void drawBoard(GLuint texture);
void quad(int, int, int, int);
void drawBall();
void killBall(double x, double y);

#endif /* _DRAWBOARD_H */
