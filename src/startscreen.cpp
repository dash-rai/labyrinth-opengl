#include <GL/glut.h>
#include <unistd.h>
#include "startscreen.h"
#include <iostream>

int w, h;
int stop = 0;

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		if (float(x)/w >= 0.4 && float(x)/w <= 0.54)
			if (float(y)/h >= 0.20 && float(y)/h <= .24) {
				stop = 1;
			}
	}
}

void putToScreen(GLuint start_t)
{
        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-2.2, -2.2, 0.5);
        glTexCoord2f(1,0);
        glVertex3f(2.2, -2.2, 0.5);
        glTexCoord2f(1,1);
        glVertex3f(2.2, 2.2, 0.5);
        glTexCoord2f(0,1);
        glVertex3f(-2.2, 2.2, 0.5);
        glEnd();
        glPopMatrix();
}

int displayStart(GLuint start_t)
{
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	glutMouseFunc(mouse);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, start_t);
	putToScreen(start_t);
	glDisable(GL_TEXTURE_2D);

	return stop;
}
