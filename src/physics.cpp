#include <GL/glut.h>
#include <math.h>
#include <Box2D/Box2D.h>
#include "drawboard.h"
#include "physics.h"

b2Body *ballBody;
extern b2World world;

void calcGravity(float *x, float *y, float rotate_x, float rotate_y)
{
        *x = sin(rotate_y * PI / 180.0) * GRAVITY;
        // As this is basically rotation of the matrix along the X axis
        // and is counter-clockwise, negate it to get the linear Y movement
        *y = sin(-rotate_x * PI / 180.0) * GRAVITY;
}

void createBallObject()
{
        b2BodyDef ballBodyDef;
        ballBodyDef.position.Set(-X + T + BALL_RADIUS, Y - T - BALL_RADIUS);
        ballBodyDef.type = b2_dynamicBody;
        ballBody = world.CreateBody(&ballBodyDef);

        b2CircleShape ballCircle;
        ballCircle.m_radius = BALL_RADIUS;

        b2FixtureDef ballFixtureDef;
        ballFixtureDef.shape = &ballCircle;
        ballFixtureDef.density = 0.1;
        ballFixtureDef.friction = 0.6;
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
                wallBox.SetAsBox(width / 2, height / 2);

                b2FixtureDef wallFixtureDef;
                wallFixtureDef.shape = &wallBox;
                wallFixtureDef.density = 0.75;
                wallFixtureDef.friction = 0.6;
                wallFixtureDef.restitution = RESTITUTION;
                wallBody->CreateFixture(&wallFixtureDef);
        }
}
