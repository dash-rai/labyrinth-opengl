#include <GL/glut.h>
#include "gamecontrol.h"
#include "drawboard.h"

void controlBoard(int current_x, int current_y)
{
        extern double rotate_x, rotate_y;
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
}

void specialKeys(int key, int x, int y)
{
        extern double rotate_y, rotate_x;

        if ((key == GLUT_KEY_RIGHT) && rotate_y <= BOARD_ROTATION_LIMIT)
                rotate_y += 2;
        else if ((key == GLUT_KEY_LEFT) && rotate_y >= -BOARD_ROTATION_LIMIT)
                rotate_y -= 2;
        else if ((key == GLUT_KEY_UP) && rotate_x >= -BOARD_ROTATION_LIMIT)
                rotate_x -= 2;
        else if ((key == GLUT_KEY_DOWN) && rotate_x <= BOARD_ROTATION_LIMIT)
                rotate_x += 2;
        glutPostRedisplay();
}
