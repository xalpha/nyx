////////////////////////////////////////////////////////////////////////////////
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

#include <Eigen/Core>

#include <nyx/gl.hpp>

/*
 *  widget.hpp
 *
 *  Created on: Aug 16, 2010
 *      Author: alex
 */


namespace nyx
{

template <typename T>
class widget
{
public:
    typedef Eigen::Matrix<T,3,1> Vector3;
    typedef Eigen::Matrix<T,4,4> Matrix4;

public:
    enum MouseButton{ NoButton, LeftButton, RightButton, MiddleButton, X1Button, X2Button };

    widget();
    virtual ~widget();

    virtual void initialize();

    void setFOV( T fov );

    virtual void draw() = 0;

    virtual void handleMousePress( int x, int y, int button );

    virtual void handleMouseMove( int x, int y );

    virtual void handleKeyboard( unsigned char key );

    virtual void handleResize( int width, int height );

    void setMV( const Matrix4& mv );

    void setBackgroundColor( const Vector3& col );

    void setBackgroundColor( T red, T green, T blue );

protected:
    int mouseTrans( int i );

    void setModelview( T azimuth, T elevation, T zoom );

    void setProjection( T fovy, T aspect, T zNear, T zFar );

    void setView();

protected:
    // camera
    T m_fov;
    int m_size[2];

    // default mouse handling
    int m_mouseX;
    int m_mouseY;
    int m_mouseButton;
    Vector3 m_view_transform; // elevation, azimutz, zoom
    Vector3 m_center; // center of rotation
    Matrix4 m_mv; // modelview matrix

    // default colors
    Vector3 m_backgroundColor;
};


/////
// Implementation
///

template<typename T>
inline widget<T>::widget() :
    m_fov(60.0),
    m_mouseX(0),
    m_mouseY(0),
    m_mouseButton(widget::NoButton)
{
    m_view_transform(0) = static_cast<T>(0.0); // elevation
    m_view_transform(1) = static_cast<T>(0.0); // azimuth
    m_view_transform(2) = static_cast<T>(-3.5); // zoom

    m_center = Vector3::Zero();

    // setup the rotation matrix
    m_mv = Matrix4::Identity();

    m_backgroundColor = Vector3::Zero();
}


template<typename T>
inline widget<T>::~widget(){}


template<typename T>
inline void widget<T>::initialize()
{
    // init openGL stuff
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE0);
    glEnable( GL_MULTISAMPLE );
    glEnable( GL_BLEND );
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_POINT_SMOOTH );
    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

    glLineWidth( 1.0f );
    glPointSize( 5.0f );
}


template<typename T>
inline void widget<T>::setFOV( T fov )
{
    m_fov = fov;
}


template<typename T>
inline void widget<T>::handleMousePress( int x, int y, int button )
{
    m_mouseButton = button;
    m_mouseX = mouseTrans(x);
    m_mouseY = mouseTrans(y);
}


template<typename T>
inline void widget<T>::handleMouseMove( int x, int y )
{
    // new Mouse Movement
    T dx = static_cast<T>( mouseTrans(x) ) - static_cast<T>(m_mouseX);
    T dy = static_cast<T>( mouseTrans(y) ) - static_cast<T>(m_mouseY);

    switch( m_mouseButton )
    {
        case widget::LeftButton :
            // Update Azimuth & Elevation
            m_view_transform(0) += dy/static_cast<T>(5.0);
            m_view_transform(1) += dx/static_cast<T>(5.0);

            // predevent big values
            m_view_transform[0] = fmod(m_view_transform(0),static_cast<T>(36000.0));
            m_view_transform[1] = fmod(m_view_transform(1),static_cast<T>(36000.0));
            break;

        case widget::RightButton :
            // Calculate relativ zoom
            float  dist = dy/static_cast<T>(50.0);

            // make zoom logarithmic
            dist *= log((fabs(m_view_transform(2)/static_cast<T>(10.0))+static_cast<T>(1.0)));

            // update global zoom
            m_view_transform(2)  += dist;
            break;
    }

    m_mouseX = mouseTrans(x);
    m_mouseY = mouseTrans(y);
}


template<typename T>
inline void widget<T>::handleKeyboard( unsigned char key )
{
    // no default behaviour
}


template<typename T>
inline void widget<T>::handleResize( int width, int height )
{
    m_size[0] = width;
    m_size[1] = height;
}


template<typename T>
inline void widget<T>::setMV( const Matrix4& mv )
{
    m_mv = mv;
}


template<typename T>
inline void widget<T>::setBackgroundColor( const Vector3& col )
{
    m_backgroundColor = col;
}


template<typename T>
inline void widget<T>::setBackgroundColor( T red, T green, T blue )
{
    m_backgroundColor(0) = red;
    m_backgroundColor(1) = green;
    m_backgroundColor(2) = blue;
}


template<typename T>
inline int widget<T>::mouseTrans( int i )
{
    int result = i;

    // clamp
    int width = m_size[0];
    if( i < 0 || i >width*5 )
        result = 0;
    else if( i > width )
        result = width;

    return result;
}


template<typename T>
inline void widget<T>::setModelview( T azimuth, T elevation, T zoom )
{
    // set modelview
    const T one = 1;
    const T zero = 0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    nyx::gl::Translate( zero, zero, zoom);	// Zoom
    nyx::gl::Rotate(elevation,one,zero,zero);	// rotate elevation
    nyx::gl::Rotate(azimuth,zero,one,zero);	// rotate azimuth
    nyx::gl::MultMatrix( m_mv.data() );
    nyx::gl::Translate( -m_center(0), -m_center(1), -m_center(2) );
}


template<typename T>
inline void widget<T>::setProjection( T fovy, T aspect, T zNear, T zFar )
{
    // set projection
    glViewport(0,0, m_size[0], m_size[1] );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    Eigen::Matrix4d m = Eigen::Matrix4d::Zero();
    double radians = static_cast<double>(fovy) / 2.0 * 3.1415926535897932384626433 / 180.0;
    double deltaZ = static_cast<double>(zFar - zNear);
    double sine = sin(radians);
    if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
    {
        return;
    }
    double cotangent = cos(radians) / sine;

    m(0,0) = cotangent / static_cast<double>(aspect);
    m(1,1) = cotangent;
    m(2,2) = -static_cast<double>(zFar + zNear) / deltaZ;
    m(2,3) = -2 * static_cast<double>(zNear * zFar) / deltaZ;
    m(3,2) = -1;
    m(3,3) = 0;
    nyx::gl::MultMatrix( m.data() );
}


template<typename T>
inline void widget<T>::setView()
{
    // setProjection
    setProjection( static_cast<T>(m_fov),
                   static_cast<T>(m_size[0])/static_cast<T>(m_size[1]),
                   static_cast<T>(0.002),
                   static_cast<T>(1000.0) );

    // set modelview
    setModelview( m_view_transform(1), m_view_transform(0), m_view_transform(2) );
}


} // namespace nyx
