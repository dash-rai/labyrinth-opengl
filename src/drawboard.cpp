#include <GL/glut.h>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "drawboard.h"
#include <math.h>
/* order of vertices:
   bottom-left
   top-left
   top-right
   bottom-right
   and front face first.
 */

float box_vertices[8][3] = {
        {-X, -Y, Z},
        {-X, Y, Z},
        {X, Y, Z},
        {X, -Y, Z},
        {-X, -Y, -Z},
        {-X, Y, -Z},
        {X, Y, -Z},
        {X, -Y, -Z},
};

float walls[NUMBER_OF_WALLS][8][3] = {
        {
                /* right wall */
                {X-T, -Y, Z+H},
                {X-T, Y, Z+H},
                {X, Y, Z+H},
                {X, -Y, Z+H},
                {X-T, -Y, Z},
                {X-T, Y, Z},
                {X, Y, Z},
                {X, -Y, Z},
        },
        {
                /* left wall */
                {-X, -Y, Z+H},
                {-X, Y, Z+H},
                {-X+T, Y, Z+H},
                {-X+T, -Y, Z+H},
                {-X+T, -Y, Z},
                {-X+T, Y, Z},
                {-X, Y, Z},
                {-X, -Y, Z},
        },
        {
                /* top wall */
                {-X+T, Y-T, Z+H},
                {-X+T, Y, Z+H},
                {X-T, Y, Z+H},
                {X-T, Y-T, Z+H},
                {-X+T, Y-T, Z},
                {-X+T, Y, Z},
                {X-T, Y, Z},
                {X-T, Y-T, Z},
        },
        {
                /* bottom wall */
                {-X+T, -Y, Z+H},
                {-X+T, -Y+T, Z+H},
                {X-T, -Y+T, Z+H},
                {X-T, -Y, Z+H},
                {-X+T, -Y, Z},
                {-X+T, -Y+T, Z},
                {X-T, -Y+T, Z},
                {X-T, -Y, Z},
        },
};

float holes[NUMBER_OF_HOLES][3] = {
        {-2.75, -1, Z + 0.1},
        {-1, 1.5, Z + 0.01},
        {-1, -0.5, Z + 0.01},
        {0.5, 0, Z + 0.01},
        {1, 1.75, Z + 0.01},
        {2, 0.75, Z + 0.01},
        {2, -1.25, Z + 0.01},
        {2.5, 0, Z + 0.01},
        {2.75, 0, Z + 0.01},
};

void quad(int a,int b,int c,int d,float ver[8][3])
{
        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3fv(ver[a]);
        glTexCoord2f(1,0);
        glVertex3fv(ver[b]);
        glTexCoord2f(1,1);
        glVertex3fv(ver[c]);
        glTexCoord2f(0,1);
        glVertex3fv(ver[d]);
        glEnd();
        glPopMatrix();
}

void callQuad(float ver[8][3])
{
        quad(0,3,2,1,ver);
        quad(2,3,7,6,ver);
        quad(0,4,7,3,ver);
        quad(1,2,6,5,ver);
        quad(4,5,6,7,ver);
        quad(0,1,5,4,ver);
}

void drawHole(float hole[])
{
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(hole[0], hole[1], hole[2]);
        glBegin(GL_POLYGON);
        double rad = 3.141592 / 180;
        for(double i = 0; i < rad * 360; i += rad) {
                glVertex2f(HOLE_RADIUS * cos(i),
                           HOLE_RADIUS * sin(i));
        }
        glEnd();
        glPopMatrix();
}

void drawBoard(GLuint texture)
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texture);
        callQuad(box_vertices);
        /* draw walls */
        for(int i = 0; i < NUMBER_OF_WALLS; i++)
                callQuad(walls[i]);
        /* draw holes */
        for(int i = 0; i < NUMBER_OF_HOLES; i++)
                drawHole(holes[i]);
        glDisable(GL_TEXTURE_2D);
}

void drawBall()
{
        extern b2Body *ballBody;
        b2Vec2 position = ballBody->GetPosition();

        glPushMatrix();
        glColor3f(0.74, 0.76, 0.78);
        glTranslatef(position.x, position.y, 0.5 + BALL_RADIUS);
        glutSolidSphere(BALL_RADIUS, 50, 50);
        glPopMatrix();
}

void killBall(double x, double y)
{
        printf("You just sunk into a hole at (%lf, %lf) :(\n", x, y);
        fflush(stdout);
}
