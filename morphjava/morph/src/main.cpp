#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include <GL/glut.h>
#include <ImageMagick/Magick++.h>

#include "main.hpp"


int win_width, win_height;

int xx0, yy0;
int xx1, yy1;
int snumpoints=0,dnumpoints=0;

Magick::Image simage, dimage, timage;
Magick::Blob sblob, dblob;
GLuint stexid, dtexid;


std::vector<line_t> srclines, dstlines;
point_t sp1, sp2;
point_t dp1, dp2;

using namespace Magick;

//-------------------------------------------------------------------------

//Function to initialize some basic parameters
GLvoid InitGL()
{
  //Setting the color used to clear the framebuffer
  glClearColor(0.0, 0.0, 0.0, 1.0f);
  //Setting the depth used to clear the depthbuffer
  glClearDepth(1.0);
  //Enabling Z-buffering
  glEnable(GL_DEPTH_TEST);
  //Enabling Smooth Shading 
  glShadeModel(GL_SMOOTH);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &stexid);
  glBindTexture(GL_TEXTURE_2D, stexid);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8 , 334, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, sblob.data());

  glGenTextures(1, &dtexid);
  glBindTexture(GL_TEXTURE_2D, dtexid);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8 , 334, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, dblob.data());
}

//-------------------------------------------------------------------------

//GL reshape callback
GLvoid ReshapeGL (GLsizei Width, GLsizei Height)
{
  //Prevent a divison by zero
  if (Height == 0) Height=1;
  
  //Change the matrix mode to projection
  glMatrixMode (GL_PROJECTION);
  //Load the identity matrix
  glLoadIdentity ();
  //Setup a perspective projection
  //Parameters are in the order -
  //vertical field of view angle - 60 degrees
  //Aspect Ratio i.e. width/height of window - 1.0
  //Near clipping plane distance - 0.1
  //Far clipping plane distance - 1000.0
  glOrtho( 0.0, (GLdouble)Width, 0.0, (GLdouble)Height, -1., 1. );
  //Set the viewport to the whole of the current window
  glViewport (0, 0, Width, Height);
  //Change the matrix mode to modelview
  glMatrixMode (GL_MODELVIEW);
}

//-------------------------------------------------------------------------

//GL display callback - does all the drawing
GLvoid DisplayGL()
{
  //Clear the frame and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  

  glColor3f(1.0,1.0,1.0);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, stexid);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex2f(0.0,512.0);
  glTexCoord2f(0.0, 1.0); glVertex2f(0.0,0.0);
  glTexCoord2f(1.0, 1.0); glVertex2f(334.0,0.0);
  glTexCoord2f(1.0, 0.0); glVertex2f(334.0,512.0);
  glEnd();

  glColor3f(1.0,1.0,1.0);
 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, dtexid);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex2f(335.0,512.0);
  glTexCoord2f(0.0, 1.0); glVertex2f(335.0,0.0);
  glTexCoord2f(1.0, 1.0); glVertex2f(669.0,0.0);
  glTexCoord2f(1.0, 0.0); glVertex2f(669.0,512.0);
  glEnd();
  glDisable(GL_TEXTURE_2D); 

  glPointSize(6.0);  
  glBegin(GL_POINTS);
  glColor3f(1.0, 0.0, 0.0);
  for (unsigned int i=0; i<srclines.size(); i++)
    {
      glVertex3f(srclines[i].p1.x, srclines[i].p1.y, 0.5);
      glVertex3f(srclines[i].p2.x, srclines[i].p2.y, 0.5);
    }
  glEnd();

  glLineWidth(4.0);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  for (unsigned int i=0; i<srclines.size(); i++)
    {
      glVertex3f(srclines[i].p1.x, srclines[i].p1.y, 0.5);
      glVertex3f(srclines[i].p2.x, srclines[i].p2.y, 0.5);
    }
  glEnd();

  glPointSize(6.0);  
  glBegin(GL_POINTS);
  glColor3f(0.0, 1.0, 0.0);
  for (unsigned int i=0; i<dstlines.size(); i++)
    {
      glVertex3f(dstlines[i].p1.x+335, dstlines[i].p1.y, 0.5);
      glVertex3f(dstlines[i].p2.x+335, dstlines[i].p2.y, 0.5);
    }
  glEnd();

  glLineWidth(4.0);
  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  for (unsigned int i=0; i<dstlines.size(); i++)
    {
      glVertex3f(dstlines[i].p1.x+335, dstlines[i].p1.y, 0.5);
      glVertex3f(dstlines[i].p2.x+335, dstlines[i].p2.y, 0.5);
    }
  glEnd();
  
  //Swap the double buffers
  glutSwapBuffers();
}

//-------------------------------------------------------------------------

//GL keyboard callback
GLvoid KeyPressedGL(unsigned char key, GLint x, GLint y) 
{
    switch (key)
      {    
	//quit
        case ESCAPE: exit(1);                   	
	             break;
        case 'm':
	  for (int i=0; i<=10; i++)
	    morph_frame(i,10); 
         default:
		  break;
      }	
}

void MouseGL(int button, int state, int x, int y) 
{
   if (state == GLUT_DOWN) 
     {
       if (button == GLUT_LEFT_BUTTON) 
	 {
	   if (snumpoints == 1)
	     {
	       snumpoints = 0;
	       int xx0 = x;
	       int yy0 = win_height - y;
	       sp2.x=xx0;
	       sp2.y=yy0;
	       line_t l(sp1, sp2); 
	       srclines.push_back(l);	       
	       
	     }
	   else if (snumpoints == 0)
	     {
	       int xx1 = x;
	       int yy1 =  win_height - y;
	       sp1.x=xx1;
	       sp1.y=yy1;
	       snumpoints++;
	     }
	 }
     }
   if (state == GLUT_DOWN) 
     {
       if (button == GLUT_RIGHT_BUTTON) 
	 {
	   if (dnumpoints == 1)
	     {
	       dnumpoints = 0;
	       int xx0 = x;
	       int yy0 = win_height - y;
	       dp2.x=xx0-335;
	       dp2.y=yy0;
	       line_t l(dp1, dp2); 
	       dstlines.push_back(l);	       
	       
	     }
	   else if (dnumpoints == 0)
	     {
	       int xx1 = x;
	       int yy1 =  win_height - y;
	       dp1.x=xx1-335;
	       dp1.y=yy1;
	       dnumpoints++;
	     }
	 }
     }
   glutPostRedisplay();
}       

//-------------------------------------------------------------------------

// The main rendering function
GLvoid RenderGL(int argc, char** argv)
{
  //Initialize GLUT
  glutInit(&argc, argv);
  //Initialize GLUT display
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  //Window top-left corner position
  glutInitWindowPosition(0,0 );
  //Window size
  glutInitWindowSize( 700, 512 );
  win_width=700;
  win_height=512;

  InitializeMagick(*argv);

  simage.read(Magick::Geometry(334, 512), "images/face1.jpg");
  simage.magick("RGBA");
  simage.write(&sblob,"RGBA",8);

  dimage.read(Magick::Geometry(334, 512), "images/face2.jpg");
  dimage.magick("RGBA");
  dimage.write(&dblob,"RGBA",8);

  timage = Magick::Image(Magick::Geometry(334, 512), "white");

  //Window title
  glutCreateWindow("Beier Neely Morphing");

  //Our Init function
  InitGL();

  //Register the callbacks  
  glutDisplayFunc(&DisplayGL);
  glutReshapeFunc(&ReshapeGL);  
  glutKeyboardFunc(&KeyPressedGL);
  glutMouseFunc( &MouseGL );

  //Start the GLUT event handling loop
  glutMainLoop();
}

//-------------------------------------------------------------------------

int main(int argc, char** argv)
{
  RenderGL(argc,argv);
}

//-------------------------------------------------------------------------

