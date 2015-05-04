#include <GL/glut.h>
#include <iostream>
#include "drawboard.h"
#include <SOIL/SOIL.h>
/*
 * Greater the number, the lesser the sensitivity.
 * Must be greater than 0.
 */
#define MOUSE_SENSITIVITY 4.0
#define BOARD_ROTATION_LIMIT 10.0

#define INIT_WINDOW_HEIGHT 400
#define INIT_WINDOW_WIDTH 400

using namespace std;

double rotate_y = 0, rotate_x = 0;
GLuint texture;

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

        /*
         * y coordinate provided has origin at top-left and not bottom-left.
         */
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
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(5.0, w/h, 0.1, 100.0);
        gluLookAt(0, 0, 50, 0, 0, 40, 0, 1, 0);
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        drawBoard(texture);
        glutSwapBuffers();
}

void lab_init()
{
        texture = SOIL_load_OGL_texture
                (
                        "res/woodtexture.bmp",
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                        );
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
        lab_init();
        glutMainLoop();
        return 0;
}
