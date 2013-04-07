#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include "morph.hpp"

// Defining the ESCAPE Key Code
#define ESCAPE 27

//-------------------------------------------------------------------------

GLvoid InitGL();
GLvoid ReshapeGL (GLsizei Width, GLsizei Height);
GLvoid DisplayGL();
GLvoid KeyPressedGL(unsigned char key, GLint x, GLint y);
GLvoid MouseGL(GLint key, GLint x, GLint y);
GLvoid RenderGL(int argc, char** argv);

//-------------------------------------------------------------------------

#endif
