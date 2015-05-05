#include <GL/glut.h>
#include <stdio.h>

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
                {-X+T, -Y, Z+H},
                {-X+T, Y, Z+H},
                {-X, Y, Z+H},
                {-X, -Y, Z+H},
                {-X+T, -Y, Z},
                {-X+T, Y, Z},
                {-X, Y, Z},
                {-X, -Y, Z},
        },
        {
                /* top wall */
                {X-T, Y-T, Z+H},
                {X-T, Y, Z+H},
                {-X+T, Y, Z+H},
                {-X+T, Y-T, Z+H},
                {X-T, Y-T, Z},
                {X-T, Y, Z},
                {-X+T, Y, Z},
                {-X+T, Y-T, Z},
        },
        {
                /* bottom wall */
                {X-T, -Y+T, Z+H},
                {X-T, -Y, Z+H},
                {-X+T, -Y, Z+H},
                {-X+T, -Y+T, Z+H},
                {X-T, -Y+T, Z},
                {X-T, -Y, Z},
                {-X+T, -Y, Z},
                {-X+T, -Y+T, Z},
        },
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
        glDisable(GL_TEXTURE_2D);
}
