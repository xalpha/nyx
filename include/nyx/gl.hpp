 ///////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of nyx, a lightweight C++ template library for OpenGL    //
//                                                                            //
// Copyright (C) 2010, 2011 Alexandru Duliu                                   //
//                                                                            //
// nyx is free software; you can redistribute it and/or                       //
// modify it under the terms of the GNU Lesser General Public                 //
// License as published by the Free Software Foundation; either               //
// version 3 of the License, or (at your option) any later version.           //
//                                                                            //
// nyx is distributed in the hope that it will be useful, but WITHOUT ANY     //
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS  //
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the //
// GNU General Public License for more details.                               //
//                                                                            //
// You should have received a copy of the GNU Lesser General Public           //
// License along with nyx. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                            //
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GL/glew.h>


namespace nyx
{

/*
 * gl.hpp
 *
 *  Created on: Aug 16, 2010
 *      Author: alex
 */

namespace gl
{


//template <typename T> inline void glColor3b (GLbyte red, GLbyte green, GLbyte blue);
//template <typename T> inline void glColor3bv (const GLbyte *v);

//template <typename T> inline void glColor4d (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
//template <typename T> inline void glColor4dv (const GLdouble *v);

//template <typename T> inline void glGetDoublev (GLenum pname, GLdouble *params);
//template <typename T> inline void glGetIntegerv (GLenum pname, GLint *params);

//template <typename T> inline void glIndexd (GLdouble c);
//template <typename T> inline void glIndexdv (const GLdouble *c);

template <typename T> inline void LoadMatrix (const T *m);
template <> inline void LoadMatrix (const float *m) { glLoadMatrixf(m); }
template <> inline void LoadMatrix (const double *m){ glLoadMatrixd(m); }

template <typename T> inline void MultMatrix (const T *m);
template <float> inline void MultMatrix (const float *m) { glMultMatrixf(m); }
template <float> inline void MultMatrix (const double *m){ glMultMatrixd(m); }

//template <typename T> inline void glNormal3b (GLbyte nx, GLbyte ny, GLbyte nz);
//template <typename T> inline void glNormal3bv (const GLbyte *v);

template <typename T> inline void Rotate (T angle, T x, T y, T z);
template <> inline void Rotate (float angle, float x, float y, float z)    { glRotatef(angle,x,y,z); }
template <> inline void Rotate (double angle, double x, double y, double z){ glRotated(angle,x,y,z); }

template <typename T> inline void Scale (T x, T y, T z);
template <> inline void Scale (float x, float y, float z)   { glScalef(x,y,z); }
template <> inline void Scale (double x, double y, double z){ glScaled(x,y,z); }

//template <typename T> inline void glTexCoord1d (GLdouble s);
//template <typename T> inline void glTexCoord1dv (const GLdouble *v);

//template <typename T> inline void glTexCoord2d (GLdouble s, GLdouble t);
//template <typename T> inline void glTexCoord2dv (const GLdouble *v);

//template <typename T> inline void glTexCoord3d (GLdouble s, GLdouble t, GLdouble r);
//template <typename T> inline void glTexCoord3dv (const GLdouble *v);

//template <typename T> inline void glTexCoord4d (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
//template <typename T> inline void glTexCoord4dv (const GLdouble *v);

template <typename T> inline void Translate (T x, T y, T z);
template <> inline void Translate (float x, float y, float z)   { glTranslatef(x,y,z); }
template <> inline void Translate (double x, double y, double z){ glTranslated(x,y,z); }

//template <typename T> inline void glVertex2d (GLdouble x, GLdouble y);
//template <typename T> inline void glVertex2dv (const GLdouble *v);

//template <typename T> inline void glVertex3d (GLdouble x, GLdouble y, GLdouble z);
//template <typename T> inline void glVertex3dv (const GLdouble *v);

//template <typename T> inline void glVertex4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
//template <typename T> inline void glVertex4dv (const GLdouble *v);



} // end namespace gl
