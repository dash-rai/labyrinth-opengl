#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <Box2D/Box2D.h>
#include "drawboard.h"
#include "startscreen.h"
#include "gamecontrol.h"
#include "physics.h"

double rotate_y = 0, rotate_x = 0;
GLuint wood_t, start_t, wall_t;
b2World world(b2Vec2(0, 0));    // Create Box2D world with 0 gravity
b2Vec2 hole_position;
bool gameover = false;

void initTextures()
{
        wood_t = SOIL_load_OGL_texture
                (
                 "res/woodtexture.jpg",
                 SOIL_LOAD_AUTO,
                 SOIL_CREATE_NEW_ID,
                 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                 SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                 );
        start_t = SOIL_load_OGL_texture
                (
                 "res/startscreen.png",
                 SOIL_LOAD_AUTO,
                 SOIL_CREATE_NEW_ID,
                 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                 SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                 );
        wall_t = SOIL_load_OGL_texture
                (
                 "res/walltexture.jpg",
                 SOIL_LOAD_AUTO,
                 SOIL_CREATE_NEW_ID,
                 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                 SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                 );
}

void initLabyrinth()
{
        initTextures();
        createBallObject();
        createWallObjects();
        createHoleObjects();
}

void step()
{
        extern b2Body *ballBody;

        if (glutGet(GLUT_ELAPSED_TIME) % (1000/60)) {
                float force_x, force_y;
                calcGravity(&force_x, &force_y, rotate_x, rotate_y);
                if (gameover) {
                        // when the ball touches the hole
                        b2Vec2 ball_pos = ballBody->GetPosition();
                        ballBody->ApplyForceToCenter(
                                b2Vec2(
                                        // magnify the force
                                        100 * (hole_position.x - ball_pos.x),
                                        100 * (hole_position.y - ball_pos.y)
                                        ),
                                true);
                        b2Vec2 velocity = ballBody->GetLinearVelocity();
                        // decrease velocity until 0
                        if (velocity.x > 0)
                                velocity.x -= 0.5;
                        else
                                velocity.x = 0;
                        if (velocity.y > 0)
                                velocity.y -= 0.5;
                        else
                                velocity.y = 0;
                        ballBody->SetLinearVelocity(velocity);
                } else {
                        // normal gameplay
                        ballBody->ApplyForceToCenter(b2Vec2(force_x, force_y),
                                                     true);
                }
                world.Step(1.0f/60.0f, 6, 2);
                glutPostRedisplay();
        }
}

void display()
{
        static int start = 0;

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluPerspective(5.0, w/h, 0.1, 100.0);
        if (!start) {
                gluLookAt(0, 0, 50, 0, 0, 40, 0, 1, 0);
                start = displayStart(start_t);
        } else {
                glutPassiveMotionFunc(controlBoard);
                gluLookAt(0, 0, 80, 0, 0, 60, 0, 1, 0);
                glRotatef(rotate_x, 1.0, 0.0, 0.0);
                glRotatef(rotate_y, 0.0, 1.0, 0.0);
                drawBall();
                drawBoard(wood_t, wall_t);
        }
        glutSwapBuffers();
}

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("Labyrinth");
        glutDisplayFunc(display);
        glutSpecialFunc(specialKeys);
        glEnable(GL_DEPTH_TEST);
        initLabyrinth();
        glutIdleFunc(step);
        glutMainLoop();

        return 0;
}
