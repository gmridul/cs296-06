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


namespace cs296
{
	dominos_t::dominos_t()
	{
		float g1_l=4.0, g1_b=0.2, g1_x=-45.0, g1_y=40.0;
		float g2_l=12.0, g2_b=0.20, g2_x=-31.0, g2_y=31.0;
		float g3_l=2.0, g3_b=0.4, g3_x=18.0, g3_y=21.0;
		float g4_l=2.0, g4_b=0.4, g4_x=29.4, g4_y=40.0;
		float g5_l=3.0, g5_b=0.2, g5_x=42.0, g5_y=21.0;
		float g6_l=7.0, g6_b=14, g6_x=40.0, g6_y=0.0;

		float offset1=2.0, offset2=1.5, pendulum1_l=6.9, r1=0.5; //pendulum    

		float domino1_l=0.1, domino1_b=1.5, offset3=1.5, offset4=1.25; //dominos

		float r2=2.0, r3=1.6, offset5=3.0, offset6=3.0;
		float bs1_l=3.0, bs1_b=0.2, bs2_l=0.2, bs2_b=1;
		float r4=1.6, pulley_y=26.0, rope_l=4.0;
		float r5=1.6, r6=0.5, r7=0.2, offset7=0.2, stick_l=g6_l-2*r5-g5_l/2.0, stick_b=0.4;
		float stick_x=g5_x-stick_l, stick_y=g6_y+g6_b+stick_b;
		float plank_l=6.0, plank_b=0.2, plank_x=g1_x, plank_y=-4.0;
		float box_l=1.5, box_b=1.5, box_x=plank_x-plank_l+box_l/2.0, box_y=plank_y+plank_b+box_b;
		float pulplank_x=plank_x+plank_l+1.0,pulplank_y= 3.0-box_y;
		float box2_x=pulplank_x+plank_l+2.0, box2_y=plank_y;
		float slide1_i=0.25,r8=2.0;
		float gear_x=-14.0f, gear_y=6.0f, offset8=2.0f;
		/* *****************************Parabolic curved slide1 --SUDIPTO--  */
		for(float left=-12;left!=18;left=left+slide1_i)
		{
			b2PolygonShape p_shape;				
			p_shape.SetAsBox(dist(left,left*left/18,left+slide1_i,(left+slide1_i)*(left+slide1_i)/18)/2.0, 0.05); //! Create a g1_shape as a box g1_l m wide and g1_b m high
			b2BodyDef p_bd;
			p_bd.position.Set(15+left+slide1_i/2.0, -4 + (left*left/18 + (left+slide1_i)*(left+slide1_i)/18)/2.0); //! Position the body on (g1_x, g1_y)
			p_bd.angle=theta(left,left*left/18,left+slide1_i,left+slide1_i*left+slide1_i/4)*b2_pi;
			b2Body* p_b2 = m_world->CreateBody(&p_bd); //! Create the body
			p_b2->CreateFixture(&p_shape, 0.0f);
		}
		/*****************************************************/


		/* *****************************Parabolic curved slide2 --SUDIPTO--  */
		for(float left=-20;left!=14;left=left+slide1_i)
		{
			b2PolygonShape p_shape;				
			p_shape.SetAsBox(dist(left,left*left/22,left+slide1_i,(left+slide1_i)*(left+slide1_i)/22)/2.0, 0.05); //! Create a g1_shape as a box g1_l m wide and g1_b m high
			b2BodyDef p_bd;
			p_bd.position.Set(2 +left+slide1_i/2.0, 11 + (left*left/22 + (left+slide1_i)*(left+slide1_i)/18)/2.0); //! Position the body on (g1_x, g1_y)
			p_bd.angle=theta(left,left*left/22,left+slide1_i,left+slide1_i*left+slide1_i/4)*b2_pi;
			b2Body* p_b2 = m_world->CreateBody(&p_bd); //! Create the body
			p_b2->CreateFixture(&p_shape, 0.0f);
		}
		/*************************************************************/
		// for g1
		b2PolygonShape g1_shape; //! Define a polygon g1_shape
		g1_shape.SetAsBox(g1_l, g1_b); //! Create a g1_shape as a box g1_l m wide and g1_b m high

		b2BodyDef g1_bd;
		g1_bd.position.Set(g1_x, g1_y); //! Position the body on (g1_x, g1_y)
		b2Body* g1_b2 = m_world->CreateBody(&g1_bd); //! Create the body
		g1_b2->CreateFixture(&g1_shape, 0.0f); //! Create the fixture of the body

		// for sphere1
		b2Body* sphere1_body;
		b2CircleShape circle1; //! Create a circle shape
		circle1.m_radius = r1; //! Set the radius of the balls to be r1 m

		b2FixtureDef ball1_fd;
		ball1_fd.shape = &circle1;
		ball1_fd.density = 0.1f; //! Set the density to be unity
		ball1_fd.friction = 0.00f; //! No friction to allow the balls to roll freely
		ball1_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		//create four pendulums in the loop


		for (int i = 0; i < 4; ++i)
		{
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set (g1_x + offset1 - offset2*i, g1_y - pendulum1_l);
			sphere1_body = m_world->CreateBody(&ballbd);
			sphere1_body->CreateFixture(&ball1_fd);
			b2RevoluteJointDef jd; //! Define the revolute joint
			b2Vec2 anchor;
			anchor.Set(g1_x + offset1 - offset2*i, g1_y); //! Set the anchor of the body (around which the pendulum will rotate)
			jd.Initialize(g1_b2, sphere1_body, anchor); //! Initialise the joint to be between g1_b2 and sphere1_body
			m_world->CreateJoint(&jd); //! Create the joint
		}

		// for g2
		b2PolygonShape g2_shape; //! Define a polygon g2_shape
		g2_shape.SetAsBox(g2_l, g2_b); //! Create a g2_shape as a box g2_l m wide and g2_b m high

		b2BodyDef g2_bd;
		g2_bd.position.Set(g2_x, g2_y); //! Position the body on (g2_x, g2_y)
		b2Body* g2_b2 = m_world->CreateBody(&g2_bd); //! Create the body
		g2_b2->CreateFixture(&g2_shape, 0.0f); //! Create the fixture of the body

		//! Dominos
		b2PolygonShape domino_shape;
		domino_shape.SetAsBox(domino1_l, domino1_b); // Create a domino_shape as a box domino1_x m wide and domino1_y m high

		b2FixtureDef fd;
		fd.shape = &domino_shape;
		fd.density = 20.0f; //! Since the dominos are not static and also rotating, the density is non-zero
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

		b2Body* sphere2_body;
		b2CircleShape circle2; //! Create a circle shape
		circle2.m_radius = r2; //! Set the radius of the balls to be r2 m

		b2FixtureDef ball2_fd;
		ball2_fd.shape = &circle2;
		ball2_fd.density = 5.0f; //! Set the density to be unity
		ball2_fd.friction = 0.5f; //! No friction to allow the balls to roll freely
		ball2_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		b2BodyDef ball2_bd;
		ball2_bd.type = b2_dynamicBody;
		ball2_bd.position.Set (g2_x + g2_l - r2, g2_y + g2_b + r2);
		sphere2_body = m_world->CreateBody(&ball2_bd);
		sphere2_body->CreateFixture(&ball2_fd);

		// for g3
		b2PolygonShape g3_shape; //! Define a polygon g3_shape
		g3_shape.SetAsBox(g3_l, g3_b); //! Create a g3_shape as a box g3_l m wide and g3_b m high

		b2BodyDef g3_bd;
		g3_bd.position.Set(g3_x, g3_y); //! Position the body on (g3_x, g3_y)
		b2Body* g3_b2 = m_world->CreateBody(&g3_bd); //! Create the body
		g3_b2->CreateFixture(&g3_shape, 0.0f); //! Create the fixture of the body

		b2Body* sphere3_body;
		b2CircleShape circle3; //! Create a circle shape
		circle3.m_radius = r3; //! Set the radius of the balls to be r3 m

		b2FixtureDef ball3_fd;
		ball3_fd.shape = &circle3;
		ball3_fd.density = 25.0f; //! Set the density to be 2
		ball3_fd.friction = 0.0f; //! No friction to allow the balls to roll freely
		ball3_fd.restitution = 0.5f; //! Zero restitution to allow elastic collision

		b2BodyDef ball3_bd;
		ball3_bd.type = b2_dynamicBody;
		ball3_bd.position.Set (g3_x, g3_y + g3_b + r3);
		sphere3_body = m_world->CreateBody(&ball3_bd);
		sphere3_body->CreateFixture(&ball3_fd);


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

		b2Body* spherebody;
		b2CircleShape circle; //! Create a circle shape
		circle.m_radius = 0.2; //! Set the radius of the balls to be 0.2m

		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 2.0f; //! Set the density to be unity
		ballfd.friction = 0.5f; //! No friction to allow the balls to roll freely
		ballfd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		b2BodyDef ballbd;
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set (g3_x+ g3_l + offset5 + r4*2.0, pulley_y);
		spherebody = m_world->CreateBody(&ballbd);
		spherebody->CreateFixture(&ballfd);

		//! The pulley joint
		b2PulleyJointDef* myjoint = new b2PulleyJointDef();
		b2Vec2 worldAnchorOnBody1(g3_x+ g3_l + offset5, g3_y-offset6); //! Anchor point on body 1 in world axis
		b2Vec2 worldAnchorOnBody2(g3_x+ g3_l + offset5 + r4*2.0, pulley_y); //! Anchor point on body 2 in world axis
		b2Vec2 worldAnchorGround1(g3_x+ g3_l + offset5, pulley_y + rope_l/2.0); //! Anchor point for ground 1 in world axis
		b2Vec2 worldAnchorGround2(g3_x+ g3_l + offset5 + r4*2.0, pulley_y + rope_l/2.0); //! Anchor point for ground 2 in world axis
		float32 ratio = 1.0f; //! Define ratio of the two sides for the pulley to go up and down
		myjoint->Initialize(box1, spherebody, worldAnchorGround1, worldAnchorGround2, worldAnchorOnBody1, worldAnchorOnBody2, ratio); //! Initialize the joint with the above values spherebody->GetWorldCenter()
		m_world->CreateJoint(myjoint);

		// for g4    
		b2PolygonShape g4_shape; //! Define a polygon g4_shape
		g4_shape.SetAsBox(g4_l, g4_b); //! Create a g4_shape as a box g4_l m wide and g4_b m high

		b2BodyDef g4_bd;
		g4_bd.position.Set(g4_x, g4_y); //! Position the body on (g4_x, g4_y)
		b2Body* g4_b2 = m_world->CreateBody(&g4_bd); //! Create the body
		g4_b2->CreateFixture(&g4_shape, 0.0f); //! Create the fixture of the body

		//! The pulley joint
		b2PulleyJointDef* myjoint2 = new b2PulleyJointDef();
		b2Vec2 worldAnchorOnBody3(g3_x+ g3_l + offset5 + r4*2.0, pulley_y); //! Anchor point on body 1 in world axis
		b2Vec2 worldAnchorOnBody4(g4_x, g4_y); //! Anchor point on body 2 in world axis
		b2Vec2 worldAnchorGround3(g3_x+ g3_l + offset5 + r4*2.0, pulley_y - rope_l/2.0); //! Anchor point for ground 1 in world axis
		b2Vec2 worldAnchorGround4(g3_x+ g3_l + offset5 + r4*4.0, pulley_y - rope_l/2.0); //! Anchor point for ground 2 in world axis
		float32 ratio2 = 1.0f; //! Define ratio of the two sides for the pulley to go up and down
		myjoint2->Initialize(spherebody, g4_b2, worldAnchorGround3, worldAnchorGround4, worldAnchorOnBody3, worldAnchorOnBody4, ratio2); //! Initialize the joint with the above values spherebody->GetWorldCenter()
		m_world->CreateJoint(myjoint2);

		// for g5    
		b2PolygonShape g5_shape; //! Define a polygon g5_shape
		g5_shape.SetAsBox(g5_l, g5_b); //! Create a g5_shape as a box g5_l m wide and g5_b m high

		b2BodyDef g5_bd;
		g5_bd.position.Set(g5_x, g5_y); //! Position the body on (g5_x, g5_y)
		b2Body* g5_b2 = m_world->CreateBody(&g5_bd); //! Create the body
		g5_b2->CreateFixture(&g5_shape, 0.0f); //! Create the fixture of the body

		b2Body* sphere4_body;
		b2CircleShape circle4; //! Create a circle shape
		circle4.m_radius = r6; //! Set the radius of the balls to be r6 m

		b2FixtureDef ball4_fd;
		ball4_fd.shape = &circle4;
		ball4_fd.density = 20.0f; //! Set the density to be 20
		ball4_fd.friction = 0.5f; //! No friction to allow the balls to roll freely
		ball4_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		b2BodyDef pendulum2_bd;
		pendulum2_bd.type = b2_dynamicBody;
		pendulum2_bd.position.Set (g5_x + g5_y - g6_y - g6_b - 2*r6 - offset7, g5_y);
		sphere4_body = m_world->CreateBody(&pendulum2_bd);
		sphere4_body->CreateFixture(&ball4_fd);
		b2RevoluteJointDef pendulum2_jd; //! Define the revolute joint
		b2Vec2 pendulum2_anchor;
		pendulum2_anchor.Set(g5_x, g5_y); //! Set the anchor of the body (around which the pendulum will rotate)
		pendulum2_jd.Initialize(g5_b2, sphere4_body, pendulum2_anchor); //! Initialise the joint to be between g5_b2 and sphere4_body
		m_world->CreateJoint(&pendulum2_jd); //! Create the joint


		// for g6    
		b2PolygonShape g6_shape; //! Define a polygon g6_shape
		g6_shape.SetAsBox(g6_l, g6_b); //! Create a g6_shape as a box g6_l m wide and g6_b m high

		b2BodyDef g6_bd;
		g6_bd.position.Set(g6_x, g6_y); //! Position the body on (g6_x, g6_y)
		b2Body* g6_b2 = m_world->CreateBody(&g6_bd); //! Create the body
		g6_b2->CreateFixture(&g6_shape, 0.0f); //! Create the fixture of the body

		b2Body* sphere5_body;
		b2CircleShape circle5; //! Create a circle shape
		circle5.m_radius = r5; //! Set the radius of the balls to be r5 m

		b2FixtureDef ball5_fd;
		ball5_fd.shape = &circle5;
		ball5_fd.density = 5.0f; //! Set the density to be 5
		ball5_fd.friction = 0.0f; //! No friction to allow the balls to roll freely
		ball5_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		b2BodyDef ball5_bd;
		ball5_bd.type = b2_dynamicBody;
		ball5_bd.position.Set (g6_x - g6_l + r5, g6_y + g6_b + r5);
		sphere5_body = m_world->CreateBody(&ball5_bd);
		sphere5_body->CreateFixture(&ball5_fd);

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

		b2Body* sphere6_body;
		b2CircleShape circle6; //! Create a circle shape
		circle6.m_radius = r7; //! Set the radius of the balls to be r7 m

		b2FixtureDef ball6_fd;
		ball6_fd.shape = &circle6;
		ball6_fd.density = 5.0f; //! Set the density to be unity
		ball6_fd.friction = 0.0f; //! No friction to allow the balls to roll freely
		ball6_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		b2BodyDef ball6_bd;
		ball6_bd.type = b2_staticBody;
		ball6_bd.position.Set (plank_x, com.y);
		sphere6_body = m_world->CreateBody(&ball6_bd);
		sphere6_body->CreateFixture(&ball6_fd);

		b2RevoluteJointDef jointDef; // this code block will join the plank with the ball
		jointDef.bodyA = plank_body;
		jointDef.bodyB = sphere6_body;
		jointDef.localAnchorA.Set(0.0f,0.0f); //SUDIPTO I added added these two lines
		jointDef.localAnchorB.Set(0.0f,0.0f);

		b2RevoluteJoint* joint = (b2RevoluteJoint*)m_world->CreateJoint(&jointDef);


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

		//Now defining the sphere to hinge pulplank
		b2Body* sphere8_body;

		b2FixtureDef ball8_fd;
		ball8_fd.shape = &circle6;
		ball8_fd.density = 5.0f; //! Set the density to be unity
		ball8_fd.friction = 0.0f; //! No friction to allow the balls to roll freely
		ball8_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		b2BodyDef ball8_bd;
		ball8_bd.type = b2_staticBody;
		ball8_bd.position.Set(pulplank_x,pulplank_y+plank_b);
		sphere8_body = m_world->CreateBody(&ball8_bd);
		sphere8_body->CreateFixture(&ball8_fd);

		b2RevoluteJointDef jointDef2; // this code block will join the plank with the ball
		jointDef2.bodyA = pulplank_body;
		jointDef2.bodyB = sphere8_body;
		jointDef2.localAnchorA.Set(0.0f,0.0f); 
		jointDef2.localAnchorB.Set(0.0f,0.0f);

		b2RevoluteJoint* joint2 = (b2RevoluteJoint*)m_world->CreateJoint(&jointDef2);


		// now placing sphere7 on pulplank	
		b2Body* sphere7_body;

		b2FixtureDef ball7_fd;
		ball7_fd.shape = &circle4;
		ball7_fd.density = 55.0f; //! Set the density to be unity
		ball7_fd.friction = 0.0f; //! No friction to allow the balls to roll freely
		ball7_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		b2BodyDef ball7_bd;

		ball7_bd.type = b2_dynamicBody;
		ball7_bd.position.Set(pulplank_x,pulplank_y+plank_b+r6 );
		sphere7_body = m_world->CreateBody(&ball7_bd);
		sphere7_body->CreateFixture(&ball7_fd);

		// defining the rod  system which will get hit by the flying block

		b2BodyDef plankfly_bd;
		plankfly_bd.type = b2_dynamicBody;
		plankfly_bd.angle=b2_pi*0.25f;
		plankfly_bd.fixedRotation = false;
		plankfly_bd.position.Set((plank_x+pulplank_x)/2.0, plank_y+20.0);
		b2Body* plankfly_body = m_world->CreateBody(&plankfly_bd);
		plankfly_body->CreateFixture(&plank_fd);    

		b2Body* sphere9_body;

		b2BodyDef ball9_bd;
		ball9_bd.type = b2_staticBody;
		ball9_bd.position.Set ((plank_x+pulplank_x)/2.0, plank_y+20.0);
		sphere9_body = m_world->CreateBody(&ball9_bd);
		sphere9_body->CreateFixture(&ball6_fd);

		b2RevoluteJointDef flyjointDef; // this code block will join the plank with the ball
		flyjointDef.bodyA = plankfly_body;
		flyjointDef.bodyB = sphere9_body;
		flyjointDef.localAnchorA.Set(0.0f,0.0f);
		flyjointDef.localAnchorB.Set(0.0f,0.0f);

		b2RevoluteJoint* flyjoint = (b2RevoluteJoint*)m_world->CreateJoint(&flyjointDef);

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

		b2Body* sphere10_body; // the sphere which works as a hinge for plankpend.

		b2BodyDef ball10_bd;
		ball10_bd.type = b2_staticBody;
		ball10_bd.position.Set (box_x+2.0, plank_y+30.0);
		sphere10_body = m_world->CreateBody(&ball10_bd);
		sphere10_body->CreateFixture(&ball6_fd);

		b2RevoluteJointDef pendjointDef; // this code block will join the plank with the ball
		pendjointDef.bodyA = plankpend_body;
		pendjointDef.bodyB = sphere10_body;
		pendjointDef.localAnchorA.Set(0.0f,0.0f);
		pendjointDef.localAnchorB.Set(0.0f,0.0f);

		b2RevoluteJoint* pendjoint = (b2RevoluteJoint*)m_world->CreateJoint(&pendjointDef);
		
		b2Body* gear_body;
		 b2CircleShape circle11; //! Create a circle shape
		 circle11.m_radius = r8; //! Set the radius of the balls to be r2 m

		 b2FixtureDef ball11_fd;
		 ball11_fd.shape = &circle11;
		 ball11_fd.density = 5.0f; //! Set the density to be unity
		 ball11_fd.friction = 0.000f; //! No friction to allow the balls to roll freely
		 ball11_fd.restitution = 0.0f; //! Zero restitution to allow elastic collision

		 b2BodyDef ball11_bd;
		 ball11_bd.type = b2_dynamicBody;
		 ball11_bd.position.Set (gear_x,gear_y);
		 gear_body = m_world->CreateBody(&ball11_bd);
		 gear_body->CreateFixture(&ball2_fd);		

		 b2Body* sphere11_body;

		 b2BodyDef ball12_bd;
		 ball12_bd.type = b2_staticBody;
		 ball12_bd.position.Set (gear_x,gear_y);
		 sphere11_body = m_world->CreateBody(&ball12_bd);
		 sphere11_body->CreateFixture(&ball6_fd);
		
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
		 // b2FixtureDef *gear_proj_2 = new b2FixtureDef; //! Define two new fixtures representing the right and left walls of the box
		 // gear_proj_2->density = 0.0;//! Set their density to be zero
		 // gear_proj_2->friction = 0; //! Set the friction coefficient
		 // gear_proj_2->restitution = 0.f; //! Allow for elastic collision
		 // gear_proj_2->shape = new b2PolygonShape; //! Define a new polygon shape
		 // b2PolygonShape stick2; //! Define another polygon shape variable
		 // stick2.SetAsBox(4, 0.2, b2Vec2(-4-0.1, -4), 0); //! Set the right and left walls as rectangular boxes
		 gear_proj->shape = &stick1;
		 // gear_proj->shape = &stick2;
		 gear_body->CreateFixture(gear_proj);
		 // gear_body->CreateFixture(gear_proj_2);
	

		// this is the rod which will drive the gear into motion
		 b2RevoluteJointDef gearjointDef; // this code block will join the plank with the ball
		 gearjointDef.bodyA = gear_body;
		 gearjointDef.bodyB = sphere11_body;
		 gearjointDef.localAnchorA.Set(0.0f,0.0f);
		 gearjointDef.localAnchorB.Set(0.0f,0.0f);

		 b2RevoluteJoint* gearjoint = (b2RevoluteJoint*)m_world->CreateJoint(&gearjointDef);

		 b2BodyDef plankgear_bd;
		plankgear_bd.type = b2_dynamicBody;
		plankgear_bd.fixedRotation = false;
		plankgear_bd.position.Set(-3.0,8.0);
		b2Body* plankgear_body = m_world->CreateBody(&plankgear_bd);
		plankgear_body->CreateFixture(&plank_fd);    

		b2Body* sphere12_body;

		b2BodyDef ball13_bd;
		ball13_bd.type = b2_staticBody;
		ball13_bd.position.Set (-3.0,8.0);
		sphere12_body = m_world->CreateBody(&ball13_bd);
		sphere12_body->CreateFixture(&ball6_fd);

		b2RevoluteJointDef geardriverjointDef; // this code block will join the plank with the ball
		geardriverjointDef.bodyA = plankgear_body;
		geardriverjointDef.bodyB = sphere12_body;
		geardriverjointDef.localAnchorA.Set(0.0f,0.0f);
		geardriverjointDef.localAnchorB.Set(0.0f,0.0f);

		// b2PolygonShape puller_shape;
		// puller_shape.SetAsBox(0.1,5); // Create a puller_shape as a box domino1_x m wide and domino1_y m high

		// b2FixtureDef puller_fd;
		// puller_fd.shape = &puller_shape;
		// puller_fd.density = 20.0f; //! Since the dominos are not static and also rotating, the density is non-zero
		// puller_fd.friction = 0.5f; //! Non-zero friction will help the dominos come to a halt on the top horizontal shelf when they are hit by the pendulum

		// b2BodyDef puller_bd;
		// puller_bd.type = b2_dynamicBody; //! Define the domino to be a dynamic body
		// puller_bd.position.Set(g2_x - g2_l + offset3 + offset4 * i, g2_y+ g2_b + domino1_b); //! Set the positions of the dominos starting at (g2_x - g2_l + offset3, 22.85f) and separated by a horizontal distance of offset4 m
		// b2Body* body = m_world->CreateBody(&puller_bd);
		// body->CreateFixture(&puller_fd);

		b2RevoluteJoint* geardriverjoint = (b2RevoluteJoint*)m_world->CreateJoint(&geardriverjointDef);

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

		//! The open box2
		b2BodyDef *dynamic_bd2 = new b2BodyDef; //! Define a new body
		dynamic_bd2->type = b2_dynamicBody; //! Set its type as dynamic
		dynamic_bd2->position.Set(box2_x+offset8,box2_y); //! Set its initial position at (g3_x+ g3_l + offset5, g3_y - offset6)
		dynamic_bd2->fixedRotation = true; //! Set the rotational inertia of the block to be zero, i.e. Don't allow the block to rotate when the ball fall on the block

		b2Body* box2 = m_world->CreateBody(dynamic_bd2); //! Create the body
		box2->CreateFixture(dynamic_fd1); //! Add the fixtures of the base and the two walls to the body
		box2->CreateFixture(dynamic_fd2);
		box2->CreateFixture(dynamic_fd3);
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
