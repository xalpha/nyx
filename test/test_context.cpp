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

#include <GL/glew.h>
#include <GL/glut.h>

#include <nyx/test.hpp>
#include <nyx/context.hpp>

/*
 * test_context.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: alex
 */

/////
// GLUT callbacks
///
void idlefunc(void){ glutPostRedisplay(); }
void reshapefunc(int width,int height){}
void motionfunc(int x,int y){}
void keyboardfunc(unsigned char key,int x,int y){}
void displayfunc()
{
    // clear buffer
    glClearColor( rand()/255,rand()/255,rand()/255,1 );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void mousefunc(int button,int state,int x,int y){}


int main( int argc, char** argv )
{
    // init glut
    glutInit(&argc,argv);

    // initial size of viewport (client area of window)
    glutInitWindowSize(800,600);

    // Requests a double RGB-framebuffer with depth- and stencil-buffer
    glutInitDisplayMode( GLUT_RGBA| GLUT_DEPTH );

    // Creates the window.
    glutCreateWindow( "nyx: test context" );

    // init stuff
    nyx::context<GLuint> c;

    // init context
    c.init();

    // check if the context is ok
    if( !c.ok() )
        throw std::runtime_error( "nyx::text_context: no context." );

    // print the status of the context
    c.status();

    // get the version of the context
    c.version();

    return 0;
}

