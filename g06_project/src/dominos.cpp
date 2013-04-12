#include "cs296_base.hpp"
#include "render.hpp"
#include<math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"
float dist(float x1, float y1, float x2, float y2)
{
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

float theta(float x1, float y1, float x2, float y2)
{
  if (x1==x2)
    return 0.5;
  return atan((y2-y1)/(x2-x1))/3.1415942;
}

float parabola(float x,int c)
{
  return x*x/c;
}

b2Body* make_box (b2World* m_world, float l, float b, float x, float y, bool if_static = true, bool if_fixedRotation = true, float angle = 0.0f)
{
  b2PolygonShape box_shape; //! Define a polygon box_shape
  box_shape.SetAsBox(l, b); //! Create a box_shape as a box l m wide and b m high
  b2BodyDef box_bd;
  if (if_static == false)
    box_bd.type = b2_dynamicBody;
  box_bd.angle = b2_pi * angle;
  box_bd.fixedRotation = if_fixedRotation;
  box_bd.position.Set(x, y); //! Position the body on (x, y)
  b2Body* box_b2 = m_world->CreateBody(&box_bd); //! Create the body
  box_b2->CreateFixture(&box_shape, 0.0f); //! Create the fixture of the body
  return box_b2;
}

b2Body* make_sphere (b2World* m_world, float r, float x, float y, float density = 0.0f, float friction = 0.0f, float restitution = 0.0f, bool if_static = true)
{
  // Create a sphere body
  b2Body* sphere_body;
  b2CircleShape circle; //! Create a circle shape
  circle.m_radius = r; //! Set the radius of the balls to be r m
  
  b2FixtureDef ball_fd;
  ball_fd.shape = &circle;
  ball_fd.density = density; //! Set the density
  ball_fd.friction = friction; //! Set the friction
  ball_fd.restitution = restitution; //! Set the restitution
  
  b2BodyDef ballbd;
  if (if_static == true)
    ballbd.type = b2_staticBody;
  else
    ballbd.type = b2_dynamicBody;
  ballbd.position.Set (x, y);
  sphere_body = m_world->CreateBody(&ballbd);
  sphere_body->CreateFixture(&ball_fd);

  return sphere_body;
}

namespace cs296
{
  dominos_t::dominos_t()
  {
    float g1_l=4.0, g1_b=0.2, g1_x=-43.0, g1_y=40.0;
    float g2_l=11.0, g2_b=0.20, g2_x=-29.0, g2_y=31.0;
    float g3_l=2.0, g3_b=0.4, g3_x=19.0, g3_y=20.0;
    float g4_l=4.0, g4_b=0.4, g4_x=29.4, g4_y=40.0;
    float g5_l=3.0, g5_b=0.2, g5_x=42.0, g5_y=21.0;
    float g6_l=7.0, g6_b=14, g6_x=40.0, g6_y=0.0;

    float offset1=2.0, offset2=1.5, pendulum1_l=6.9, r1=0.5; //pendulum    

    float domino1_l=0.1, domino1_b=1.5, offset3=1.5, offset4=1.25; //dominos

    float r2=2.0, r3=1.6, offset5=3.0, offset6=4.0;
    float bs1_l=3.0, bs1_b=0.2, bs2_l=0.2, bs2_b=1.5;
    float r4=1.6, pulley_y=26.0, rope_l=4.0;
    float r5=1.6, r6=0.5, r7=0.2, offset7=0.2, stick_l=g6_l-2*r5-g5_l/2.0, stick_b=0.4;
    float stick_x=g5_x-stick_l, stick_y=g6_y+g6_b+stick_b;
    float plank_l=6.0, plank_b=0.2, plank_x=g1_x, plank_y=-4.0;
    float box_l=1.5, box_b=1.5, box_x=plank_x-plank_l+box_l/5.0, box_y=plank_y+plank_b+box_b;
    float pulplank_x=plank_x+plank_l+1.0,pulplank_y= 3.0-box_y;
    float box2_x=pulplank_x+plank_l+2.0, box2_y=plank_y;
    float slide1_i=0.25,r8=2.0;
    float gear_x=-14.0f, gear_y=6.0f, offset8=2.0f;
    float b_box1l = 56.0f, b_box1b = 0.2f, b_box1x = -6.0f, b_box1y = -14.0f;
    float b_box2l = 35.0f, b_box2b = 0.2f, b_box2x = 50.0f, b_box2y = 21.0f;

    make_box (m_world, b_box1l, b_box1b, b_box1x, b_box1y);
    make_box (m_world, b_box2l, b_box2b, b_box2x, b_box2y, true, true, 0.5f);
    make_box (m_world, b_box1l, b_box1b, b_box1x, b_box1y + b_box2l * 2.0f);
    make_box (m_world, b_box2l, b_box2b, b_box2x - b_box1l * 2.0f, b_box2y, true, true, 0.5f);

    /* *****************************Parabolic curved slide1 */
    for(float left=-12;left!=18;left=left+slide1_i)
      {
	float parabola_l = dist(left,parabola(left,18),left+slide1_i,parabola(left+slide1_i,18))/2.0, 
	  parabola_x = 15+left+slide1_i/2.0,
	  parabola_y = -4 + (parabola(left,18) + parabola(left+slide1_i,18))/2.0, 
	  angle = theta (left, parabola(left,18), left+slide1_i, parabola(left+slide1_i,18));
	make_box (m_world, parabola_l, 0.05, parabola_x, parabola_y, true, true, angle);
      }
    /*****************************************************/

    /* *****************************Parabolic curved slide2 */
    for(float left=-22;left!=12.5;left=left+slide1_i)
      {
	float parabola_l = dist(left,parabola(left,30),left+slide1_i,parabola(left+slide1_i,30))/2.0,
	  parabola_x = 4 +left+slide1_i/2.0,
	  parabola_y = 15 + (parabola(left,30) + parabola(left+slide1_i,30))/2.0,
	  angle = theta (left,parabola(left,30),left+slide1_i,parabola(left+slide1_i,30));
	make_box (m_world, parabola_l, 0.05, parabola_x, parabola_y, true, true, angle);
      }
    /*************************************************************/

    b2Body* g1_b2 = make_box (m_world, g1_l, g1_b, g1_x, g1_y, true);

    for (int i=0; i < 4; ++i)
      {
	b2Body* sphere1_body = make_sphere(m_world, r1, g1_x + offset1 - offset2*i, g1_y - pendulum1_l, 0.1, 0.05, 0.0, false);
	b2RevoluteJointDef jd; //! Define the revolute joint
    	b2Vec2 anchor;
    	anchor.Set(g1_x + offset1 - offset2*i, g1_y); //! Set the anchor of the body (around which the pendulum will rotate)
    	jd.Initialize(g1_b2, sphere1_body, anchor); //! Initialise the joint to be between g1_b2 and sphere1_body
    	m_world->CreateJoint(&jd); //! Create the joint
      }

    make_box (m_world, g2_l, g2_b, g2_x, g2_y, true);

    //! Dominos
    b2PolygonShape domino_shape;
    domino_shape.SetAsBox(domino1_l, domino1_b); // Create a domino_shape as a box domino1_x m wide and domino1_y m high

    b2FixtureDef fd;
    fd.shape = &domino_shape;
    fd.density = 10.0f; //! Since the dominos are not static and also rotating, the density is non-zero
    fd.friction = 0.5f; //! Non-zero friction will help the dominos come to a halt on the top horizontal shelf when they are hit by the pendulum

    //! define the 15 dominos
    for (int i = 0; i < 15; ++i)
      {
    	b2BodyDef bd;
    	bd.type = b2_dynamicBody; //! Define the domino to be a dynamic body
    	bd.position.Set(g2_x - g2_l + offset3 + offset4 * i, g2_y+ g2_b + domino1_b); //! Set the positions of the dominos starting at (g2_x - g2_l + offset3, 22.85f) and separated by a horizontal distance of offset4 m
    	b2Body* body = m_world->CreateBody(&bd);
    	body->CreateFixture(&fd);
      }
    
    make_sphere (m_world, r2, g2_x + g2_l, g2_y + g2_b + r2, 5.0f, 0.5f, 0.0f, false);

    make_box (m_world, g3_l, g3_b, g3_x, g3_y, true);

    make_sphere (m_world, r3, g3_x, g3_y + g3_b + r3, 25.0f, 0.05f, 0.5f, false);

    //! The pulley system
    //! The open box
    b2BodyDef *dynamic_bd = new b2BodyDef; //! Define a new body
    dynamic_bd->type = b2_dynamicBody; //! Set its type as dynamic
    dynamic_bd->position.Set(g3_x+ g3_l + offset5, g3_y - offset6); //! Set its initial position at (g3_x+ g3_l + offset5, g3_y - offset6)
    dynamic_bd->fixedRotation = true; //! Set the rotational inertia of the block to be zero, i.e. Don't allow the block to rotate when the ball fall on the block

    b2FixtureDef *dynamic_fd1 = new b2FixtureDef; //! Define a new fixture for the base of the box
    dynamic_fd1->density = 10.0; //! Set its density to be 10.0
    dynamic_fd1->friction = 0.5; //! Set the friction coefficient to be non-zero so that the ball doesn't move on the block after they fall on it
    dynamic_fd1->restitution = 0.f; //! Set the coefficient of restitution to be zero to allow for elastic collisions between the balls and the block
    dynamic_fd1->shape = new b2PolygonShape; //! Define a new polygon shape
    b2PolygonShape bs1; //! Define another polygon shape variable
    bs1.SetAsBox(bs1_l,bs1_b, b2Vec2(0.0f,0.0f), 0); //! Set the base as a rectangular box 
    dynamic_fd1->shape = &bs1;
    b2FixtureDef *dynamic_fd2 = new b2FixtureDef; //! Define two new fixtures representing the right and left walls of the box
    dynamic_fd2->density = 10.0;//! Set their density to be zero
    dynamic_fd2->friction = 0.5; //! Set the friction coefficient
    dynamic_fd2->restitution = 0.f; //! Allow for elastic collision
    dynamic_fd2->shape = new b2PolygonShape; //! Define a new polygon shape
    b2PolygonShape bs2; //! Define another polygon shape variable
    bs2.SetAsBox(bs2_l,bs2_b, b2Vec2(-bs1_l, bs2_b/2.0 + bs1_b), 0); //! Set the right and left walls as rectangular boxes
    dynamic_fd2->shape = &bs2;
    b2FixtureDef *dynamic_fd3 = new b2FixtureDef;  
    dynamic_fd3->density = 10.0;
    dynamic_fd3->friction = 0.5;
    dynamic_fd3->restitution = 0.f;
    dynamic_fd3->shape = new b2PolygonShape;
    b2PolygonShape bs3;
    bs3.SetAsBox(bs2_l,bs2_b, b2Vec2(bs1_l, bs2_b/2.0 + bs1_b), 0);
    dynamic_fd3->shape = &bs3;
    b2Body* box1 = m_world->CreateBody(dynamic_bd); //! Create the body
    box1->CreateFixture(dynamic_fd1); //! Add the fixtures of the base and the two walls to the body
    box1->CreateFixture(dynamic_fd2);
    box1->CreateFixture(dynamic_fd3);
    box1->SetGravityScale(0);

    b2Body* support_body1 = make_sphere (m_world, 0.0f, g3_x + g3_l + offset5 + r4*2.0, pulley_y, 2.0f, 0.5f, 0.0f, false);

    //! The pulley joint
    b2PulleyJointDef* myjoint = new b2PulleyJointDef();
    b2Vec2 worldAnchorOnBody1(g3_x+ g3_l + offset5, g3_y-offset6); //! Anchor point on body 1 in world axis
    b2Vec2 worldAnchorOnBody2(g3_x+ g3_l + offset5 + r4*2.0, pulley_y); //! Anchor point on body 2 in world axis
    b2Vec2 worldAnchorGround1(g3_x+ g3_l + offset5, pulley_y + rope_l/2.0); //! Anchor point for ground 1 in world axis
    b2Vec2 worldAnchorGround2(g3_x+ g3_l + offset5 + r4*2.0, pulley_y + rope_l/2.0); //! Anchor point for ground 2 in world axis
    float32 ratio = 1.0f; //! Define ratio of the two sides for the pulley to go up and down
    myjoint->Initialize(box1, support_body1, worldAnchorGround1, worldAnchorGround2, worldAnchorOnBody1, worldAnchorOnBody2, ratio); //! Initialize the joint with the above values support_body1->GetWorldCenter()
    m_world->CreateJoint(myjoint);

    b2Body* support_body2 = make_sphere (m_world, 0.0f, g4_x, pulley_y, 2.0f, 0.5f, 0.0f, false);
    //! The pulley joint
    b2PulleyJointDef* myjoint2 = new b2PulleyJointDef();
    b2Vec2 worldAnchorOnBody3(g3_x+ g3_l + offset5 + r4*2.0, pulley_y); //! Anchor point on body 1 in world axis
    b2Vec2 worldAnchorOnBody4(g4_x, pulley_y); //! Anchor point on body 2 in world axis
    b2Vec2 worldAnchorGround3(g3_x+ g3_l + offset5 + r4*2.0, pulley_y - rope_l/2.0); //! Anchor point for ground 1 in world axis
    b2Vec2 worldAnchorGround4(g4_x, pulley_y - rope_l/2.0); //! Anchor point for ground 2 in world axis
    float32 ratio2 = 1.0f; //! Define ratio of the two sides for the pulley to go up and down
    myjoint2->Initialize(support_body1, support_body2, worldAnchorGround3, worldAnchorGround4, worldAnchorOnBody3, worldAnchorOnBody4, ratio2); //! Initialize the joint with the above values support_body1->GetWorldCenter()
    m_world->CreateJoint(myjoint2);

    // b2Body* g4_b2 = make_box (m_world, g4_l, g4_b, g4_x + 10.0, g4_y-10.0f, false, false);

    b2PolygonShape final_plank_shape;
    final_plank_shape.SetAsBox(g4_l, g4_b);

    b2FixtureDef final_plank_fd;
    final_plank_fd.shape = &final_plank_shape;
    final_plank_fd.density = 1.0f;
    final_plank_fd.friction = 0.01f;
    final_plank_fd.restitution = 0.0f;

    b2BodyDef final_plank_bd;
    final_plank_bd.type = b2_dynamicBody;
    final_plank_bd.fixedRotation = false;
    final_plank_bd.position.Set(g4_x + 10.0f, g4_y - 10.0f);
    b2Body* final_plank_body = m_world->CreateBody(&final_plank_bd);
    final_plank_body->CreateFixture(&final_plank_fd);  

    b2Body* final_sphere_body = make_sphere (m_world, r7, g4_x + 10.0f, g4_y - 10.0f, 5.0f, 0.05f, 0.0f, true);

    b2RevoluteJointDef finaljointDef; // this code block will join the plank with the ball
    finaljointDef.bodyA = final_plank_body;
    finaljointDef.bodyB = final_sphere_body;
    finaljointDef.localAnchorA.Set(0.0f,0.0f); 
    finaljointDef.localAnchorB.Set(0.0f,0.0f);

    m_world->CreateJoint(&finaljointDef);


    //! The pulley joint
    b2PulleyJointDef* myjoint3 = new b2PulleyJointDef();
    b2Vec2 worldAnchorOnBody5(g4_x, pulley_y); //! Anchor point on body 1 in world axis
    b2Vec2 worldAnchorOnBody6(g4_x + 10.0f + g4_l, g4_y-10.0f); //! Anchor point on body 2 in world axis
    b2Vec2 worldAnchorGround5(g4_x, pulley_y + 10.0); //! Anchor point for ground 1 in world axis
    b2Vec2 worldAnchorGround6(g4_x + 10.0f + g4_l, pulley_y + 10.0); //! Anchor point for ground 2 in world axis
    float32 ratio3 = 1.0f; //! Define ratio of the two sides for the pulley to go up and down
    myjoint3->Initialize(support_body2, final_plank_body, worldAnchorGround5, worldAnchorGround6, worldAnchorOnBody5, worldAnchorOnBody6, ratio3); //! Initialize the joint with the above values support_body1->GetWorldCenter()
    m_world->CreateJoint(myjoint3);

    // b2Body* hinge_body = make_sphere (m_world, 0.2, g4_x + 10.0, g4_y - 10.0f, 5.0f, 0.05f, 0.0f, true);

    // b2RevoluteJointDef storejointDef; // this code block will join the plank with the ball
    // storejointDef.bodyA = g4_b2;
    // storejointDef.bodyB = hinge_body;
    // storejointDef.localAnchorA.Set(0.0f,0.0f);
    // storejointDef.localAnchorB.Set(0.0f,0.0f);

    // m_world->CreateJoint(&storejointDef);

    for (int i = 0; i < 50; ++i)
      {
	make_sphere (m_world, 0.05, g4_x + 10.0, g4_y - 10.0f + g4_b + 0.05, 0.02f, 0.0f, 1.5f, false);
      }

    b2Body* g5_b2 = make_box (m_world, g5_l, g5_b, g5_x, g5_y, true);
    
    b2Body* sphere4_body = make_sphere (m_world, r6, g5_x + g5_y - g6_y - g6_b - 2*r6 - offset7, g5_y, 50.0f, 0.0f, 0.0f, false);

    b2RevoluteJointDef pendulum2_jd; //! Define the revolute joint
    b2Vec2 pendulum2_anchor;
    pendulum2_anchor.Set(g5_x, g5_y); //! Set the anchor of the body (around which the pendulum will rotate)
    pendulum2_jd.Initialize(g5_b2, sphere4_body, pendulum2_anchor); //! Initialise the joint to be between g5_b2 and sphere4_body
    m_world->CreateJoint(&pendulum2_jd); //! Create the joint

    make_box (m_world, g6_l, g6_b, g6_x, g6_y, true);

    make_sphere (m_world, r5, g6_x - g6_l + r5, g6_y + g6_b + r5, 20.0f, 0.0f, 0.0f, false);

    b2PolygonShape stick_shape;
    stick_shape.SetAsBox(stick_l, stick_b);

    b2FixtureDef stick_fd;
    stick_fd.shape = &stick_shape;
    stick_fd.density = 20.0f;
    stick_fd.friction = 0.01f;
    stick_fd.restitution = 0.0f;

    b2BodyDef stick_bd;
    stick_bd.type = b2_dynamicBody;
    stick_bd.position.Set(stick_x, stick_y);
    b2Body* stick_body = m_world->CreateBody(&stick_bd);
    stick_body->CreateFixture(&stick_fd);

    b2PolygonShape plank_shape;
    plank_shape.SetAsBox(plank_l, plank_b);

    b2FixtureDef plank_fd;
    plank_fd.shape = &plank_shape;
    plank_fd.density = 1.0f;
    plank_fd.friction = 0.01f;
    plank_fd.restitution = 0.0f;

    b2BodyDef plank_bd;
    plank_bd.type = b2_dynamicBody;
    plank_bd.fixedRotation = false;
    plank_bd.position.Set(plank_x, plank_y);
    b2Body* plank_body = m_world->CreateBody(&plank_bd);
    plank_body->CreateFixture(&plank_fd);    

    b2Vec2 com(plank_x+box_l*box_b*(box_x-plank_x)/(box_l*box_b+plank_l*plank_b), plank_y-plank_b);

    b2Body* sphere6_body = make_sphere (m_world, r7, plank_x, com.y, 5.0f, 0.05f, 0.0f, true);

    b2RevoluteJointDef jointDef; // this code block will join the plank with the ball
    jointDef.bodyA = plank_body;
    jointDef.bodyB = sphere6_body;
    jointDef.localAnchorA.Set(0.0f,0.0f); //SUDIPTO I added added these two lines
    jointDef.localAnchorB.Set(0.0f,0.0f);

    m_world->CreateJoint(&jointDef);

    b2PolygonShape box_shape; // code for the left block placed on the plank
    box_shape.SetAsBox(box_l, box_b);

    b2FixtureDef box_fd;
    box_fd.shape = &box_shape;
    box_fd.density = 1.0f;
    box_fd.friction = 0.01f;
    box_fd.restitution = 0.0f;

    b2BodyDef box_bd;
    box_bd.type = b2_dynamicBody;
    box_bd.position.Set(box_x, box_y);
    b2Body* box_body = m_world->CreateBody(&box_bd);
    box_body->CreateFixture(&box_fd);        

    b2PolygonShape box2_shape;         // code for the right block on the plank.
    box2_shape.SetAsBox(box_l, box_b); // this is placed so that the plank remains as it is until the ball falls on it.

    b2FixtureDef box2_fd;              // all the properties of ball2 are same as the ball
    box2_fd.shape = &box_shape;
    box2_fd.density = 1.0f;
    box2_fd.friction = 0.01f;
    box2_fd.restitution = 0.0f;

    b2BodyDef box2_bd;
    box2_bd.type = b2_dynamicBody;
    box2_bd.position.Set(box_x+2*(plank_x-box_x), box_y);
    b2Body* box2_body = m_world->CreateBody(&box2_bd);
    box2_body->CreateFixture(&box2_fd);       
    /******************************/
    // defining the lower pulley components
    //this is the pulplank (pulley plank) 
    b2PolygonShape pulplank_shape;
    pulplank_shape.SetAsBox(plank_l/2.0, plank_b);

    b2FixtureDef pulplank_fd;
    pulplank_fd.shape = &pulplank_shape;
    pulplank_fd.density = 1.0f;
    pulplank_fd.friction = 0.01f;
    pulplank_fd.restitution = 0.0f;

    b2BodyDef pulplank_bd;
    pulplank_bd.type = b2_dynamicBody;
    pulplank_bd.fixedRotation = false;
    pulplank_bd.position.Set(pulplank_x, pulplank_y);
    b2Body* pulplank_body = m_world->CreateBody(&pulplank_bd);
    pulplank_body->CreateFixture(&pulplank_fd);  

    b2Body* sphere8_body = make_sphere (m_world, r7, pulplank_x, pulplank_y, 5.0f, 0.05f, 0.0f, true);

    b2RevoluteJointDef jointDef2; // this code block will join the plank with the ball
    jointDef2.bodyA = pulplank_body;
    jointDef2.bodyB = sphere8_body;
    jointDef2.localAnchorA.Set(0.0f,0.0f); 
    jointDef2.localAnchorB.Set(0.0f,0.0f);

    m_world->CreateJoint(&jointDef2);

    make_sphere (m_world, r6, pulplank_x, pulplank_y + plank_b + r6, 70.0f, 0.05f, 0.0f, false);

    // defining the rod  system which will get hit by the flying block

    b2BodyDef plankfly_bd;
    plankfly_bd.type = b2_dynamicBody;
    plankfly_bd.angle=b2_pi*0.25f;
    plankfly_bd.fixedRotation = false;
    plankfly_bd.position.Set((plank_x+pulplank_x)/2.0, plank_y+20.0);
    b2Body* plankfly_body = m_world->CreateBody(&plankfly_bd);
    plankfly_body->CreateFixture(&plank_fd);    

    b2Body* sphere9_body = make_sphere (m_world, r7, (plank_x + pulplank_x)/2.0, plank_y + 20.0, 5.0f, 0.05f, 0.0f, true);

    b2RevoluteJointDef flyjointDef; // this code block will join the plank with the ball
    flyjointDef.bodyA = plankfly_body;
    flyjointDef.bodyB = sphere9_body;
    flyjointDef.localAnchorA.Set(0.0f,0.0f);
    flyjointDef.localAnchorB.Set(0.0f,0.0f);

    m_world->CreateJoint(&flyjointDef);

    // defining the rod system which will hit the pendulum
    b2PolygonShape plankpend_shape;
    plankpend_shape.SetAsBox(1.3*plank_l, plank_b);

    b2FixtureDef plankpend_fd;
    plankpend_fd.shape = &plankpend_shape;
    plankpend_fd.density =0.5f;
    plankpend_fd.friction = 0.01f;
    plankpend_fd.restitution = 0.0f;

    b2BodyDef plankpend_bd;
    plankpend_bd.type = b2_dynamicBody;
    plankpend_bd.angle=-b2_pi*0.25f;
    plankpend_bd.fixedRotation = false;
    plankpend_bd.position.Set(box_x+2.0, plank_y+30.0);
    b2Body* plankpend_body = m_world->CreateBody(&plankpend_bd);
    plankpend_body->CreateFixture(&plankpend_fd);    

    b2Body* sphere10_body = make_sphere (m_world, r7, box_x + 2.0, plank_y + 30.0, 5.0f, 0.05f, 0.0f, true);

    b2RevoluteJointDef pendjointDef; // this code block will join the plank with the ball
    pendjointDef.bodyA = plankpend_body;
    pendjointDef.bodyB = sphere10_body;
    pendjointDef.localAnchorA.Set(0.0f,0.0f);
    pendjointDef.localAnchorB.Set(0.0f,0.0f);

    m_world->CreateJoint(&pendjointDef);

    b2Body* gear_body = make_sphere (m_world, r8, gear_x, gear_y, 5.0f, 0.05f, 0.0f, false);

    b2Body* sphere11_body = make_sphere (m_world, 0.0f, gear_x, gear_y, 5.0f, 0.05f, 0.0f, true);
		
    b2FixtureDef *gear_proj = new b2FixtureDef; //! Define two new fixtures representing the right and left walls of the box
    gear_proj->density = 10.0;//! Set their density to be zero
    gear_proj->friction = 0.5; //! Set the friction coefficient
    gear_proj->restitution = 0.f; //! Allow for elastic collision
    gear_proj->shape = new b2PolygonShape; //! Define a new polygon shape
    b2PolygonShape stick1; //! Define another polygon shape variable
    stick1.SetAsBox(2, 0.2, b2Vec2(4, 0), 0); //! Set the right and left walls as rectangular boxes
    gear_proj->shape = &stick1;
    gear_body->CreateFixture(gear_proj);
    stick1.SetAsBox(4, 0.2, b2Vec2(-2.7, 0.0), 1.0);
    gear_proj->shape = &stick1;
    gear_body->CreateFixture(gear_proj);

    // this is the rod which will drive the gear into motion
    b2RevoluteJointDef gearjointDef; // this code block will join the plank with the ball
    gearjointDef.bodyA = gear_body;
    gearjointDef.bodyB = sphere11_body;
    gearjointDef.localAnchorA.Set(0.0f,0.0f);
    gearjointDef.localAnchorB.Set(0.0f,0.0f);

    m_world->CreateJoint(&gearjointDef);


    b2BodyDef plankgear_bd;
    plankgear_bd.type = b2_dynamicBody;
    plankgear_bd.fixedRotation = false;
    plankgear_bd.position.Set(-3.0,8.0);
    b2Body* plankgear_body = m_world->CreateBody(&plankgear_bd);
    plankgear_body->CreateFixture(&plank_fd);    

    b2Body* sphere12_body = make_sphere (m_world, 0.0f, -3.0f, 8.0f, 5.0f, 0.05f, 0.0f, true);

    b2RevoluteJointDef geardriverjointDef; // this code block will join the plank with the ball
    geardriverjointDef.bodyA = plankgear_body;
    geardriverjointDef.bodyB = sphere12_body;
    geardriverjointDef.localAnchorA.Set(0.0f,0.0f);
    geardriverjointDef.localAnchorB.Set(0.0f,0.0f);

    m_world->CreateJoint(&geardriverjointDef);


    b2BodyDef ballgr_bd;
    ballgr_bd.fixedRotation = false;
    ballgr_bd.position.Set(-18.0,1.1);
    ballgr_bd.angle=b2_pi*0.25/3.0;
    b2Body* ballgr_body = m_world->CreateBody(&ballgr_bd);

    b2PolygonShape ballgr_shape;
    ballgr_shape.SetAsBox(plank_l, plank_b);

    b2FixtureDef ballgr_fd;
    ballgr_fd.shape = &ballgr_shape;
    ballgr_fd.density = 1.0f;
    ballgr_fd.friction = 0.01f;
    ballgr_fd.restitution = 0.0f;

    ballgr_body->CreateFixture(&ballgr_fd);    

    for (int i = 0; i < 8; ++i)
      {
	make_sphere(m_world, r1, -15.0, 2.5, 0.1, 0.05, 0.0, false);
      }

    //! The open box2
    b2BodyDef *dynamic_bd2 = new b2BodyDef; //! Define a new body
    dynamic_bd2->type = b2_dynamicBody; //! Set its type as dynamic
    dynamic_bd2->position.Set(box2_x+offset8,box2_y); //! Set its initial position at (g3_x+ g3_l + offset5, g3_y - offset6)
    dynamic_bd2->fixedRotation = true; //! Set the rotational inertia of the block to be zero, i.e. Don't allow the block to rotate when the ball fall on the block

    b2Body* box2 = m_world->CreateBody(dynamic_bd2); //! Create the body
    box2->CreateFixture(dynamic_fd1); //! Add the fixtures of the base and the two walls to the body
    box2->CreateFixture(dynamic_fd2);
    box2->CreateFixture(dynamic_fd3);
    box2->SetGravityScale(0);
    //implementing pulley. First define the left part that is the part that is attached to pulplank.

    b2PulleyJointDef* ljoint2 = new b2PulleyJointDef();
    b2Vec2 worldAnchorOnBodyA(pulplank_x+plank_l/2.0,pulplank_y); //! Anchor point on body 1 in world axis
    b2Vec2 worldAnchorOnBodyB(box2_x+offset8,box2_y); //! Anchor point on body 2 in world axis
    b2Vec2 worldAnchorGroundA(pulplank_x+plank_l/2.0, pulplank_y+5.0); //! Anchor point for ground 1 in world axis
    b2Vec2 worldAnchorGroundB(box2_x+offset8,pulplank_y+5.0); //! Anchor point for ground 2 in world axis
    ljoint2->Initialize(pulplank_body, box2, worldAnchorGroundA, worldAnchorGroundB, worldAnchorOnBodyA, worldAnchorOnBodyB, ratio); //! Initialize the joint with the above values spherebody->GetWorldCenter()
    m_world->CreateJoint(ljoint2);	

    /******************************/
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
