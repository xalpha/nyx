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

#ifdef NYX_USE_EIGEN
#include <Eigen/Core>
#endif

#include <nyx/util.hpp>


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

template <typename T> inline void Color3 (T red, T green, T blue);
template <> inline void Color3 (float red, float green, float blue)   { glColor3f(red,green,blue); }
template <> inline void Color3 (double red, double green, double blue){ glColor3d(red,green,blue); }

template <typename T> inline void Color3 (const T *v);
template <> inline void Color3 (const float *v) { glColor3fv(v); }
template <> inline void Color3 (const double *v){ glColor3dv(v); }

template <typename T> inline void Color4 (T red, T green, T blue, T alpha);
template <> inline void Color4 (float red, float green, float blue, float alpha)    { glColor4f(red,green,blue,alpha); }
template <> inline void Color4 (double red, double green, double blue, double alpha){ glColor4d(red,green,blue,alpha); }

template <typename T> inline void Color4 (const T *v);
template <> inline void Color4 (const float *v) { glColor4fv(v); }
template <> inline void Color4 (const double *v){ glColor4dv(v); }

//template <typename T> inline void glGetDoublev (GLenum pname, GLdouble *params);
//template <typename T> inline void glGetIntegerv (GLenum pname, GLint *params);

//template <typename T> inline void glIndexd (GLdouble c);
//template <typename T> inline void glIndexdv (const GLdouble *c);

template <typename T> inline void ClearColor (T red, T green, T blue, T alpha){ glClearColor( static_cast<GLclampf>(red),
                                                                                              static_cast<GLclampf>(green),
                                                                                              static_cast<GLclampf>(blue),
                                                                                              static_cast<GLclampf>(alpha) ); }
#ifdef NYX_USE_EIGEN
template <typename T> inline void ClearColor ( const Eigen::Matrix<T,3,1>& col ){ ClearColor( col(0), col(1), col(2), nyx::util::type<T>::one() ); }
template <typename T> inline void ClearColor ( const Eigen::Matrix<T,4,1>& col ){ ClearColor( col(0), col(1), col(2), col(3) ); }
#endif


template <typename T> inline void LoadMatrix (const T *m);
template <> inline void LoadMatrix (const float *m) { glLoadMatrixf(m); }
template <> inline void LoadMatrix (const double *m){ glLoadMatrixd(m); }


template <typename T> inline void MultMatrix (const T *m);
template <> inline void MultMatrix (const float *m) { glMultMatrixf(m); }
template <> inline void MultMatrix (const double *m){ glMultMatrixd(m); }

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


template <typename T> inline void Vertex2 (T x, T y);
template <> inline void Vertex2 (float x, float y)  { glVertex2f(x,y); }
template <> inline void Vertex2 (double x, double y){ glVertex2d(x,y); }

template <typename T> inline void Vertex2 (const T *v);
template <> inline void Vertex2 (const float *v) { glVertex2fv(v); }
template <> inline void Vertex2 (const double *v){ glVertex2dv(v); }


template <typename T> inline void Vertex3 (T x, T y, T z);
template <> inline void Vertex3 (float x, float y, float z)  { glVertex3f(x,y,z); }
template <> inline void Vertex3 (double x, double y, double z){ glVertex3d(x,y,z); }

template <typename T> inline void Vertex3 (const T *v);
template <> inline void Vertex3 (const float *v) { glVertex3fv(v); }
template <> inline void Vertex3 (const double *v){ glVertex3dv(v); }


template <typename T> inline void Vertex4 (T x, T y, T z, T w);
template <> inline void Vertex4 (float x, float y, float z, float w)  { glVertex4f(x,y,z,w); }
template <> inline void Vertex4 (double x, double y, double z, double w){ glVertex4d(x,y,z,w); }

template <typename T> inline void Vertex4 (const T *v);
template <> inline void Vertex4 (const float *v) { glVertex4fv(v); }
template <> inline void Vertex4 (const double *v){ glVertex4dv(v); }

} // end namespace gl

} // end namespace nyx
