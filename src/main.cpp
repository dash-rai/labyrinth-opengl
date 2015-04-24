#include <GL/glut.h>
#include <iostream>

using namespace std;

double rotate_y = 0, rotate_x = 0;

float ver[8][3] = {
        {-2.0,-1.0,1.0},
        {-2.0,1.0,1.0},
        {2.0,1.0,1.0},
        {2.0,-1.0,1.0},
        {-2.0,-1.0,-1.0},
        {-2.0,1.0,-1.0},
        {2.0,1.0,-1.0},
        {2.0,-1.0,-1.0},
};

float color[4] = {0.5, 0, 1, 1};

void quad(int a,int b,int c,int d)
{
        glBegin(GL_QUADS);
        glColor3fv(color);
        glVertex3fv(ver[a]);
        glVertex3fv(ver[b]);
        glVertex3fv(ver[c]);
        glVertex3fv(ver[d]);
        glEnd();
}

void colorcube()
{
        quad(0,3,2,1);
        quad(2,3,7,6);
        quad(0,4,7,3);
        quad(1,2,6,5);
        quad(4,5,6,7);
        quad(0,1,5,4);
}

void specialKeys( int key, int x, int y )
{
        if (key == GLUT_KEY_RIGHT)
                rotate_y += 5;
        else if (key == GLUT_KEY_LEFT)
                rotate_y -= 5;
        else if (key == GLUT_KEY_UP)
                rotate_x += 5;
        else if (key == GLUT_KEY_DOWN)
                rotate_x -= 5;
        glutPostRedisplay();
}

void display()
{
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(60.0, w/h, 0.1, 100.0);
        gluLookAt(0, 0, 5, 0, 0, 2, 0, 1, 0);
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        colorcube();
        glutSwapBuffers();
}

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(400, 400);
        glutCreateWindow("Labyrinth");
        glutDisplayFunc(display);
        glutSpecialFunc(specialKeys);
        glEnable(GL_DEPTH_TEST);
        glutMainLoop();
        return 0;
}
