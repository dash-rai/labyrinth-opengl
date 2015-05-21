#include <GL/glut.h>
#include <math.h>
#include <Box2D/Box2D.h>
#include "drawboard.h"
#include "physics.h"

b2Body *ballBody;
extern b2World world;

class HoleContactListener : public b2ContactListener
{
        void BeginContact(b2Contact *contact)
        {
                /* Process only hole-ball collisions */
                if (contact->GetFixtureA()->IsSensor() ||
                    contact->GetFixtureB()->IsSensor()) {

                        b2Vec2 position = ballBody->GetPosition();
                        killBall(position.x, position.y);
                        // finishPlay();
                }
        }
};

/* Create collision listener */
HoleContactListener holeContactListenerInstance;

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
        ballFixtureDef.density = BALL_DENSITY;
        ballFixtureDef.friction = FRICTION;
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
                wallFixtureDef.density = WALL_DENSITY;
                wallFixtureDef.friction = FRICTION;
                wallFixtureDef.restitution = RESTITUTION;
                wallBody->CreateFixture(&wallFixtureDef);
        }
}

void createHoleObjects()
{
        extern float holes[NUMBER_OF_HOLES][3];

        for (int i = 0; i < NUMBER_OF_HOLES; i++) {
                b2BodyDef holeBodyDef;
                holeBodyDef.position.Set(holes[i][0], holes[i][1]);
                b2Body *holeBody = world.CreateBody(&holeBodyDef);

                b2CircleShape holeCircle;
                /*
                 * TODO: allow some leeway by reducing the size of
                 * the hole's fixture
                 */
                holeCircle.m_radius = HOLE_RADIUS;

                b2FixtureDef holeFixtureDef;
                holeFixtureDef.shape = &holeCircle;
                holeFixtureDef.isSensor = true;
                holeBody->CreateFixture(&holeFixtureDef);
                world.SetContactListener(&holeContactListenerInstance);
        }
}
