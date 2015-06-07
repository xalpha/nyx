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

#include <nyx/vis/widget.hpp>
#include <nyx/object/vertex_buffer_object.hpp>

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>


class test_widget : public QOpenGLWidget, public nyx::widget<float>
{
    Q_OBJECT

public:
    test_widget(QWidget *parent = 0);
    ~test_widget();

    // nyx functions
    virtual void draw();

    // qt functions
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void keyPressEvent(QKeyEvent * event);

protected:
    std::vector<float> m_vertices;
    std::vector<float> m_colors;
};
