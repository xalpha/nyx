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

#include <iostream>

#include <test_widget.hpp>
#include <QOpenGLShaderProgram>


test_widget::test_widget(QWidget *parent) :
    QOpenGLWidget(parent),
    nyx::widget<float>()
{
}


test_widget::~test_widget()
{
}


void test_widget::draw()
{
    // clear buffer
    nyx::gl::ClearColor( nyx::widget<float>::m_backgroundColor );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the mvp matrix
    nyx::widget<float>::setView();

    glBegin(GL_TRIANGLES);
    for( int i=0; i<m_vertices.size()/3; i++ )
    {
        glColor3fv( &m_colors[i*3] );
        glVertex3fv( &m_vertices[i*3] );
    }
    glEnd();
}


void test_widget::initializeGL()
{
    // init gl
    nyx::widget<float>::initialize();

    // init geometry
    float values[108] = {-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,-1.0f,-1.0f,-1.0f,-1.0f,1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,-1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,-1.0f,1.0f};
    for( int i=0; i<108; i++ )
    {
        m_vertices.push_back(values[i]);
        m_colors.push_back( 0.5*(values[i]+1.0f) );
    }
}


void test_widget::paintGL()
{
    draw();
}


void test_widget::resizeGL(int w, int h)
{
    handleResize(w,h);
}


void test_widget::mousePressEvent(QMouseEvent * event)
{
    switch( event->button() )
    {
        case Qt::MouseButton::LeftButton : handleMousePress( event->x(), event->y(), nyx::widget<float>::LeftButton ); break;
        case Qt::MouseButton::RightButton : handleMousePress( event->x(), event->y(), nyx::widget<float>::RightButton ); break;
    }
    update();
}

void test_widget::mouseMoveEvent(QMouseEvent * event)
{
    handleMouseMove( event->x(), event->y() );
    update();
}


void test_widget::keyPressEvent(QKeyEvent * event){}
