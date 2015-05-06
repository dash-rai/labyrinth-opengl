#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <Box2D/Box2D.h>
#include "drawboard.h"
#include "startscreen.h"
#include <math.h>

/*
 * Greater the number, the lesser the sensitivity.
 * Must be greater than 0.
 */
#define MOUSE_SENSITIVITY 4.0
#define BOARD_ROTATION_LIMIT 10.0

#define INIT_WINDOW_WIDTH 1024
#define INIT_WINDOW_HEIGHT 768

#define PI 3.14159265
#define GRAVITY 0.5
#define RESTITUTION 0.8

double rotate_y = 0, rotate_x = 0;
GLuint wood_t, start_t;
double ball_x, ball_y;
GLuint texture;
b2World world(b2Vec2(0, 0));    // Create Box2D world with 0 gravity
b2Body *ballBody;

void drawBall()
{
        glPushMatrix();
                glColor3f(0.74, 0.76, 0.78);
                glTranslatef(ball_x, ball_y, 0.6);
                glutSolidSphere(0.075, 50, 50);
        glPopMatrix();
}

void createBallObject()
{
        b2BodyDef ballBodyDef;
        ballBodyDef.position.Set(0, 0);
        ballBodyDef.type = b2_dynamicBody;
        ballBody = world.CreateBody(&ballBodyDef);

        b2PolygonShape ballBox;
        ballBox.SetAsBox(0.1, 0.1);

        b2FixtureDef ballFixtureDef;
        ballFixtureDef.shape = &ballBox;
        ballFixtureDef.density = 0.1;
        ballFixtureDef.restitution = RESTITUTION;
        ballBody->CreateFixture(&ballFixtureDef);
}

void createWallObjects()
{
        extern float walls[NUMBER_OF_WALLS][8][3];

        for(int i = 0; i < NUMBER_OF_WALLS; i++) {
                b2BodyDef wallBodyDef;
                // only works for rectangles
                float width = walls[i][2][0] - walls[i][0][0];
                float height = walls[i][2][1] - walls[i][0][1];
                width = (width < 0) ? -width : width;
                height = (height < 0) ? -height : height;
                float center_x = walls[i][0][0] + width / 2 ;
                float center_y = walls[i][0][1] + height / 2;

                wallBodyDef.position.Set(center_x, center_y);
                wallBodyDef.type = b2_staticBody;
                b2Body *wallBody = world.CreateBody(&wallBodyDef);

                b2PolygonShape wallBox;
                wallBox.SetAsBox(width, height);

                b2FixtureDef wallFixtureDef;
                wallFixtureDef.shape = &wallBox;
                wallFixtureDef.density = 0.75;
                wallFixtureDef.restitution = RESTITUTION;
                wallBody->CreateFixture(&wallFixtureDef);
        }
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
                drawBoard(wood_t);
        }
        glutSwapBuffers();
}

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
}

void initLabyrinth()
{
        initTextures();
        createBallObject();
        createWallObjects();
}

void calcGravity(float *x, float *y)
{
        *x = sin(rotate_y * PI / 180.0) * GRAVITY;
        // As this is basically rotation of the matrix along the X axis
        // and is counter-clockwise, negate it to get the linear Y movement
        *y = sin(-rotate_x * PI / 180.0) * GRAVITY;
}

void step()
{
        if (glutGet(GLUT_ELAPSED_TIME) % (1000/60)) {
                float force_x, force_y;
                calcGravity(&force_x, &force_y);
                ballBody->ApplyForceToCenter(b2Vec2(force_x, force_y), true);
                world.Step(1.0f/60.0f, 6, 2);
                b2Vec2 position = ballBody->GetPosition();
                ball_x = position.x;
                ball_y = position.y;
                glutPostRedisplay();
        }
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
