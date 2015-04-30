#include <GL/glut.h>
#include <stdio.h>

float ver[8][3] = {
        {-2.0, -2.0, 0.5},
        {-2.0, 2.0, 0.5},
        {2.0, 2.0, 0.5},
        {2.0, -2.0, 0.5},
        {-2.0, -2.0, -0.5},
        {-2.0, 2.0, -0.5},
        {2.0, 2.0, -0.5},
        {2.0, -2.0, -0.5},
};

void quad(int a,int b,int c,int d)
{
        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3fv(ver[a]);
        glTexCoord2f(5,0);
        glVertex3fv(ver[b]);
        glTexCoord2f(5,5);
        glVertex3fv(ver[c]);
        glTexCoord2f(0,5);
        glVertex3fv(ver[d]);
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
        quad(0,3,2,1);
        quad(2,3,7,6);
        quad(0,4,7,3);
        quad(1,2,6,5);
        quad(4,5,6,7);
        quad(0,1,5,4);
        glDisable(GL_TEXTURE_2D);
}
