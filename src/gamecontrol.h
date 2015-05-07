#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

/*
 * Greater the number, the lesser the sensitivity.
 * Must be greater than 0.
 */
#define MOUSE_SENSITIVITY 8.0
#define BOARD_ROTATION_LIMIT 10.0

void controlBoard(int current_x, int current_y);
void specialKeys(int key, int x, int y);

#endif
