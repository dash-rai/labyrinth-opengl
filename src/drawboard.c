#include <GL/glut.h>

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
        glBegin(GL_QUADS);
        glVertex3fv(ver[a]);
        glVertex3fv(ver[b]);
        glVertex3fv(ver[c]);
        glVertex3fv(ver[d]);
        glEnd();
}

void drawBoard()
{
        glColor3f(1, 0, 0);
        quad(0,3,2,1);
        glColor3f(0, 0, 1);
        quad(2,3,7,6);
        glColor3f(0, 1, 0);
        quad(0,4,7,3);
        glColor3f(0, 1, 1);
        quad(1,2,6,5);
        glColor3f(1, 0, 1);
        quad(4,5,6,7);
        glColor3f(1, 1, 0);
        quad(0,1,5,4);
}
