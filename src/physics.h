#ifndef _PHYSICS_H
#define _PHYSICS_H

#define PI 3.14159265
#define GRAVITY 5
#define RESTITUTION 0.5
#define BALL_DENSITY 8.05
#define WALL_DENSITY 0.0009
#define FRICTION 0.6

void calcGravity(float *x, float *y, float rotate_x, float rotate_y);
void createBallObject();
void createWallObjects();

#endif
