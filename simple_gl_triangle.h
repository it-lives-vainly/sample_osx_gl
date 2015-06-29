// -*- mode: c++; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 *
 * create    : <2015-02-14 16:31:35 it_lives_vainly>
 * $Id$
 */
#ifndef __H_SIMPLE_GL_TRIANGLE__
#define __H_SIMPLE_GL_TRIANGLE__

#include <OpenGL/gl3.h>

namespace gl_sample{

GLint InitShaderProgram();
GLint CreateProgram(GLint vs, GLint fs);
void TestDraw();

} // end ns gl_sample

#endif // __H_SIMPLE_GL_TRIANGLE__
//===
// EOF
//===
