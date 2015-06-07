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

#include <test_mesh.hpp>
#include <QOpenGLShaderProgram>


test_mesh::test_mesh(const std::string &path) :
    QOpenGLWidget(),
    nyx::widget<float>()
{
    // I know this is bad, but it greatly simplifies the code
    m_mesh.load( path );
}


test_mesh::~test_mesh()
{
}


void test_mesh::draw()
{
    // clear buffer
    nyx::gl::ClearColor( nyx::widget<float>::m_backgroundColor );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the mvp matrix
    nyx::widget<float>::setView();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m_mesh.vertices().data());
    glDrawElements(GL_QUADS, m_mesh.indices().size(), GL_UNSIGNED_INT, m_mesh.indices().data());
    glDisableClientState(GL_VERTEX_ARRAY);
}


void test_mesh::initializeGL()
{
    // init gl
    nyx::widget<float>::initialize();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}


void test_mesh::paintGL()
{
    draw();
}


void test_mesh::resizeGL(int w, int h)
{
    handleResize(w,h);
}


void test_mesh::mousePressEvent(QMouseEvent * event)
{
    switch( event->button() )
    {
        case Qt::MouseButton::LeftButton : handleMousePress( event->x(), event->y(), nyx::widget<float>::LeftButton ); break;
        case Qt::MouseButton::RightButton : handleMousePress( event->x(), event->y(), nyx::widget<float>::RightButton ); break;
    }
    update();
}

void test_mesh::mouseMoveEvent(QMouseEvent * event)
{
    handleMouseMove( event->x(), event->y() );
    update();
}


void test_mesh::keyPressEvent(QKeyEvent * event){}
