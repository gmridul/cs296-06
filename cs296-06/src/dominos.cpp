/*
 * Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  {
    //! ~~~~~~~~~~~~~~~~~~~
    //! Ground
    b2Body* b1;
    {
      b2EdgeShape shape; //! Define an edge shape
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f)); //! Set the shape as a horizontal line 180m long stretching from (-90m,0) to (+90m,0)
      
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd); //! Create the body ground
      b1->CreateFixture(&shape, 0.0f); //! Create the fixture of the body with arguments shape and zero density
    }
    //! ~~~~~~~~~~~~~~~~~~~

    //! ~~~~~~~~~~~~~~~~~~~
    //! Top horizontal shelf
    {
      b2PolygonShape shape; //! Define a polygon shape
      shape.SetAsBox(6.0f, 0.25f); //! Create a shape as a box 12m wide and 0.5m high
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f); //! Position the body on (-45m,30m)
      b2Body* ground = m_world->CreateBody(&bd); //! Create the body
      ground->CreateFixture(&shape, 0.0f); //! Create the fixture of the body
    }
    //! ~~~~~~~~~~~~~~~~~~~

    //! ~~~~~~~~~~~~~~~~~~~
    //! Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f); // Create a shape as a box 0.1m wide and 10m high
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f; //! Since the dominos are not static and also rotating, the density is non-zero
      fd.friction = 0.1f; //! Non-zero friction will help the dominos come to a halt on the top horizontal shelf when they are hit by the pendulum
      
      //! define the 10 dominos
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody; //! Define the domino to be a dynamic body
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f); //! Set the positions of the dominos starting at (-35.5m,31.25m) and separated by a horizontal distance of 1m
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    //! ~~~~~~~~~~~~~~~~~~~

    //! ~~~~~~~~~~~~~~~~~~~      
    //! Another horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f); //! Define a box 7m wide and 0.25m high centered at (-20m,20m) with one side(width) at zero angle with the horizontal
      
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f); //! Shift the body 1m right and 6m up 
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //! ~~~~~~~~~~~~~~~~~~~      

    //! ~~~~~~~~~~~~~~~~~~~      
    //! The pendulum that knocks the dominos off
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f,1.5f); //! Create the vertical box to which the string of the pendulum is attached
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f); //! Set the position of the box
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f); //! Set the density of the box as 10kg/m^3
      }
      
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f); //! The pendulum itself as a small square
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody; //! Define it to be a dynamic body
	bd.position.Set(-40.0f, 33.0f); //! The initial position of the pendulum
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f); //! Set the density of the pendulum to be 2 units
      }
      
      b2RevoluteJointDef jd; //! Define the revolute joint
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f); //! Set the anchor of the body (around which the pendulum will rotate)
      jd.Initialize(b2, b4, anchor); //! Initialise the joint to be between b2 and b4
      m_world->CreateJoint(&jd); //! Create the joint
    }
    //! ~~~~~~~~~~~~~~~~~~~      
      
    //! ~~~~~~~~~~~~~~~~~~~      
    //! The train of small spheres
    {
      b2Body* spherebody;
      
      b2CircleShape circle; //! Create a circle shape
      circle.m_radius = 0.5; //! Set the radius of the balls to be 0.5m
      
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f; //! Set the density to be unity
      ballfd.friction = 0.0f; //! No friction to allow the balls to roll freely
      ballfd.restitution = 0.0f; //! Zero restitution to allow elastic collision
      
      //! Define the ten balls in a loop
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody; //! Define the ball to be dynamic
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f); //! Position the balls on the horizontal platform at a distance of 1m 
	  spherebody = m_world->CreateBody(&ballbd); //! Create the body
	  spherebody->CreateFixture(&ballfd); //! Set the fixture
	}
    }
    //! ~~~~~~~~~~~~~~~~~~~      

    //! ~~~~~~~~~~~~~~~~~~~      
    //! The pulley system
    {
      //! The open box
      b2BodyDef *bd = new b2BodyDef; //! Define a new body
      bd->type = b2_dynamicBody; //! Set its type as dynamic
      bd->position.Set(-10,15); //! Set its initial position at (-10,15)
      bd->fixedRotation = true; //! Set the rotational inertia of the block to be zero, i.e. Don't allow the block to rotate when balls fall on the block
      
      b2FixtureDef *fd1 = new b2FixtureDef; //! Define a new fixture for the base of the box
      fd1->density = 10.0; //! Set its density to be 10.0
      fd1->friction = 0.5; //! Set the friction coefficient to be non-zero so that the balls don't move on the block after they fall on it
      fd1->restitution = 0.f; //! Set the coefficient of restitution to be zero to allow for elastic collisions between the balls and the block
      fd1->shape = new b2PolygonShape; //! Define a new polygon shape
      b2PolygonShape bs1; //! Define another polygon shape variable
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0); //! Set the base as a rectangular box 
      fd1->shape = &bs1;
      //!
      b2FixtureDef *fd2 = new b2FixtureDef; //! Define two new fixtures representing the right and left walls of the box
      fd2->density = 10.0;//! Set their density to be zero
      fd2->friction = 0.5; //! Set the friction coefficient
      fd2->restitution = 0.f; //! Allow for elastic collision
      fd2->shape = new b2PolygonShape; //! Define a new polygon shape
      b2PolygonShape bs2; //! Define another polygon shape variable
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0); //! Set the right and left walls as rectangular boxes
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;  
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
      //!
      
      b2Body* box1 = m_world->CreateBody(bd); //! Create the body
      box1->CreateFixture(fd1); //! Add the fixtures of the base and the two walls to the body
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      //! - - -      
      //! The bar
      bd->position.Set(10,15); //! Position the bar at (10,15)
      fd1->density = 34.0; //! Set its density high to keep the balance at both sides of the pulley
      b2Body* box2 = m_world->CreateBody(bd); //! Create the body
      box2->CreateFixture(fd1); //! Set its fixture

      //! The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); //! Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); //! Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); //! Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); //! Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; //! Define ratio of the two sides for the pulley to go up and down
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio); //! Initialize the joint with the above values
      m_world->CreateJoint(myjoint);
    }
    //! ~~~~~~~~~~~~~~~~~~~      

    //! ~~~~~~~~~~~~~~~~~~~      
    //! The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);//! Define the shape as a box
      
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);//! Set its position
      bd.type = b2_dynamicBody; //! Set its type to be dynamic
      b2Body* body = m_world->CreateBody(&bd); //! Create the body
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f; //! Define the density to be 1
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd); //! Create the fixture
      
      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2); //! Create a very small rectangular body about which the platform can revolve

      b2RevoluteJointDef jointDef; //! Join the two bodies by a revolute joint
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false; //! Do not allow the two bodies to collide with each other
      m_world->CreateJoint(&jointDef);
    }
    //! ~~~~~~~~~~~~~~~~~~~      

    //! ~~~~~~~~~~~~~~~~~~~      
    //! The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle; //! Define the shape to be a circle
      circle.m_radius = 1.0; //! Define its radius to be 1m
      
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f; //! Define the density to be 50 units so that it is very heavy
      ballfd.friction = 0.0f; //! Set the friction to be zero
      ballfd.restitution = 0.0f; //! Allow for elastic collision
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody; //! Define the sphere to be dynamic
      ballbd.position.Set(14.0f, 18.0f); //! Set its position to (14,18)m
      sbody = m_world->CreateBody(&ballbd); //! Create the body
      sbody->CreateFixture(&ballfd); //! Create the fixture
    }
    //! ~~~~~~~~~~~~~~~~~~~      

    //! ~~~~~~~~~~~~~~~~~~~      
    //! The see-saw system at the bottom
    {
      //! The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly; //! Define a polygon shape
      b2Vec2 vertices[3]; //! Create a three tuple vector specifying the three vertices of the wedge
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3); //! Set the polygon to be the triangle between these vertices
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f; //! Set the density to be 10.0 units
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd); //! Create the wedge and attach the polygon to its fixture
      //!
      b2PolygonShape shape; //! The plank on top of the wedge
      shape.SetAsBox(15.0f, 0.2f); //! Set the shape to be a box
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f); //! Set the position of the plank
      bd2.type = b2_dynamicBody; //! Define it to be a dynamic body
      b2Body* body = m_world->CreateBody(&bd2); // Create the plank
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f; // Define the density to be 1
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2); // Define the fixture with the box shape

      //!
      b2RevoluteJointDef jd; //! Create the revolute joint between the plank and the wedge
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f); //! Set the position of the anchor
      jd.Initialize(sbody, body, anchor); //! Initialise the joint between the two bodies with the anchor
      m_world->CreateJoint(&jd);

      //! The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f); //! Set the shape to be a square box
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f); //! Set the position to be on top of the plank on the right side
      bd3.type = b2_dynamicBody; //! Set its type to be dynamic
      b2Body* body3 = m_world->CreateBody(&bd3); //! Create the body
      b2FixtureDef *fd3 = new b2FixtureDef; //! Create the fixture
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
    //! ~~~~~~~~~~~~~~~~~~~      
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
