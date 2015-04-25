#include <GL/glut.h>
#include <iostream>

#define INIT_WINDOW_HEIGHT 400
#define INIT_WINDOW_WIDTH 400

// Greater the number, the lesser the sensitivity. Must be greater than 0
#define MOUSE_SENSITIVITY 4.0
#define BOARD_ROTATION_LIMIT 10.0

using namespace std;

double rotate_y = 0, rotate_x = 0;

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

void colorcube()
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

void specialKeys(int key, int x, int y)
{
        if ((key == GLUT_KEY_RIGHT) && rotate_y <= 10)
                rotate_y += 5;
        else if ((key == GLUT_KEY_LEFT) && rotate_y >= -10)
                rotate_y -= 5;
        else if ((key == GLUT_KEY_UP) && rotate_x >= -10)
                rotate_x -= 5;
        else if ((key == GLUT_KEY_DOWN) && rotate_x <= 10)
                rotate_x += 5;
        glutPostRedisplay();
}

void controlBoard(int current_x, int current_y)
{
        static int previous_x = (INIT_WINDOW_WIDTH / 2);
        static int previous_y = (INIT_WINDOW_HEIGHT / 2);
        float delta_x, delta_y;

        // y coordinate provided has origin at top-left and not bottom-left.
        current_y = glutGet(GLUT_WINDOW_HEIGHT) - current_y;
        delta_x = (float) (current_x - previous_x) / MOUSE_SENSITIVITY;
        delta_y = (float) (current_y - previous_y) / MOUSE_SENSITIVITY;

        if ((rotate_y + delta_x) < BOARD_ROTATION_LIMIT &&
            (rotate_y + delta_x) > -BOARD_ROTATION_LIMIT)
                rotate_y += delta_x;
        if ((rotate_x - delta_y) < BOARD_ROTATION_LIMIT &&
            (rotate_x - delta_y) > -BOARD_ROTATION_LIMIT)
                rotate_x -= delta_y;

        previous_x = current_x;
        previous_y = current_y;
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
        gluPerspective(35.0, w/h, 0.1, 100.0);
        gluLookAt(0, 0, 8, 0, 0, 4, 0, 1, 0);
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        colorcube();
        glutSwapBuffers();
}

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(INIT_WINDOW_HEIGHT, INIT_WINDOW_WIDTH);
        glutCreateWindow("Labyrinth");
        glutDisplayFunc(display);
        glutSpecialFunc(specialKeys);
        glEnable(GL_DEPTH_TEST);
        glutPassiveMotionFunc(controlBoard);
        glutMainLoop();
        return 0;
}
