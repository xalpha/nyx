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

#include <GL/glew.h>
#include <GL/glut.h>

#include <nyx/vis/widget.hpp>

/*
 * test_widget.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: alex
 */


/////
// extends widget by a basic draw function
///

template <typename T>
class test_widget : public nyx::widget<T>
{
public:
    test_widget() : nyx::widget<T>(){}
    virtual ~test_widget(){}

    virtual void draw()
    {
        // clear buffer
        nyx::gl::ClearColor( nyx::widget<T>::m_backgroundColor );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set the mvp matrix
        nyx::widget<T>::setView();

        // draw teapot
        glColor3f(1,1,1);
        glutSolidTeapot( 0.5 );

        // update buffer
        glutSwapBuffers();
    }
};


/////
// Instances
///
static test_widget<float> s_test_widget;


/////
// GLUT callbacks
///
void idlefunc(void){ glutPostRedisplay(); }
void reshapefunc(int width,int height){ s_test_widget.handleResize( width, height ); }
void motionfunc(int x,int y){ s_test_widget.handleMouseMove( x,y ); }
void keyboardfunc(unsigned char key,int x,int y){ s_test_widget.handleKeyboard( key ); }
void displayfunc(){ s_test_widget.draw(); }
void mousefunc(int button,int state,int x,int y)
{
    switch( button )
    {
        case GLUT_LEFT_BUTTON : s_test_widget.handleMousePress( x,y,test_widget<float>::LeftButton ); break;
        case GLUT_RIGHT_BUTTON : s_test_widget.handleMousePress( x,y,test_widget<float>::RightButton ); break;
    }
}


int main( int argc, char** argv )
{
    // init glut
    glutInit(&argc,argv);

    // initial size of viewport (client area of window)
    glutInitWindowSize(800,600);

    // Requests a double RGB-framebuffer with depth- and stencil-buffer
    glutInitDisplayMode( GLUT_MULTISAMPLE| GLUT_RGBA| GLUT_DEPTH );

    // Creates the window.
    glutCreateWindow( "nyx: test widget" );

    // init GLEW
    int err = glewInit();
    if (GLEW_OK != err)	{
        // problem: glewInit failed, something is seriously wrong
        std::cerr << "nyx::test_widget: GLEW error: \"" << glewGetErrorString(err) << "\"." << std::endl;

        exit(-1);
    }

    // Register the callback-functions. These are then executed by GLUT
    // as soon as the main loop is entered (see below)
    glutDisplayFunc(displayfunc);
    glutReshapeFunc(reshapefunc);
    glutMouseFunc(mousefunc);
    glutMotionFunc(motionfunc);
    glutKeyboardFunc(keyboardfunc);
    glutIdleFunc(idlefunc);

    s_test_widget.initialize();

    // Enter GLUT main loop. Main loop will be terminated only
    // on user request by exit(0). Other means do not currently exist in GLUT.
    glutMainLoop();

    return 0;
}

