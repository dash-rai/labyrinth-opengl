#ifndef _DRAWBOARD_H
#define _DRAWBOARD_H

#define NUMBER_OF_WALLS 18
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

#define WALL_UNIT 0.5
#define X_BLOCK(N) ((-X + T) + ((((X - T)/X)*N) * WALL_UNIT))
#define Y_BLOCK(N) ((-Y + T) + ((((Y - T)/Y)*N) * WALL_UNIT))
#define INIT_WINDOW_WIDTH 1024
#define INIT_WINDOW_HEIGHT 768
#define BALL_RADIUS 0.075

void drawBoard(GLuint, GLuint);
void quad(int, int, int, int);
void drawBall();

#endif /* _DRAWBOARD_H */
