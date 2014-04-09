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
#include <stdint.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <nyx/vis/plot.hpp>
#include <Eigen/Geometry>



/*
 * test_plot.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: alex
 */


/////
// Instances
///
static nyx::plot<float> s_plot;
static size_t count = 1000;


/////
// GLUT callbacks
///
void idlefunc(void){ glutPostRedisplay(); }
void reshapefunc(int width,int height){ s_plot.handleResize( width, height ); }
void motionfunc(int x,int y){ s_plot.handleMouseMove( x,y ); }
void keyboardfunc(unsigned char key,int x,int y){ s_plot.handleKeyboard( key ); }
void displayfunc(){ s_plot.draw(); glutSwapBuffers(); }
void mousefunc(int button,int state,int x,int y)
{
    switch( button )
    {
        case GLUT_LEFT_BUTTON : s_plot.handleMousePress( x,y,nyx::plot<float>::LeftButton ); break;
        case GLUT_RIGHT_BUTTON : s_plot.handleMousePress( x,y,nyx::plot<float>::RightButton ); break;
    }
}


/////
// Test Plotting functionds
//
void fuzzyCube( const Eigen::Vector3f& pos, float size, const Eigen::Vector4f& color, uint32_t layer )
{
    std::vector<Eigen::Vector3f> points;
    points.reserve(count);
    for( size_t i=0; i<count; i++ )
        points.push_back( size * Eigen::Vector3f::Random() + pos );

    s_plot.setColor( color );
    s_plot( points, nyx::plot<float>::Pos | nyx::plot<float>::CS | layer );
}


void fuzzyAffines()
{
    std::vector<Eigen::Matrix4f> trans;
    trans.reserve(count/10);
    for( size_t i=0; i<count/10; i++ )
    {
        Eigen::Vector3f x = Eigen::Vector3f::Random();
        Eigen::Vector3f y = Eigen::Vector3f::Random();

        x.normalize();
        y.normalize();

        Eigen::Vector3f z = x.cross(y);
        z.normalize();

        y = z.cross(x);
        y.normalize();

        Eigen::Affine3f t = Eigen::Affine3f::Identity();
        Eigen::Matrix3f r = Eigen::Matrix3f::Identity();

        r.col(0) = x;
        r.col(1) = y;
        r.col(2) = z;

        t.rotate(r);
        t.translate( 0.5f * Eigen::Vector3f::Random() + Eigen::Vector3f(0.5,0.5,0.5) );

        trans.push_back( t.matrix() );
    }

    s_plot.setColor( Eigen::Vector4f(1,0,0,1) );
    s_plot.setLineWidth( 3.0 );
    s_plot( trans, nyx::plot<float>::Pos | nyx::plot<float>::CS );
}


void alignedAffines()
{
    s_plot.setColor( Eigen::Vector4f(0,0,0,1) );
    s_plot.setLineWidth( 1.0 );
    for( size_t i=0; i<count; i++ )
    {
        Eigen::Affine3f t = Eigen::Affine3f::Identity();
        t.rotate(Eigen::Matrix3f::Identity());
        t.translate( 0.5f * Eigen::Vector3f::Random() + Eigen::Vector3f(0.5,0.5,0.5) );

        s_plot( t.matrix(), nyx::plot<float>::Pos | nyx::plot<float>::CS );
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
    glutCreateWindow( "nyx: test plot" );

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

    // plot some stuff
    s_plot.initialize();
    s_plot.setPointSize( 3 );
    fuzzyCube( Eigen::Vector3f(1,1,0), 0.125, Eigen::Vector4f(1,1,0,1), nyx::plot<float>::Layer4 );
    fuzzyCube( Eigen::Vector3f(0,1,1), 0.125, Eigen::Vector4f(0,1,1,1), nyx::plot<float>::Layer5 );
    fuzzyCube( Eigen::Vector3f(1,0,1), 0.125, Eigen::Vector4f(1,0,1,1), nyx::plot<float>::Layer6 );
    fuzzyCube( Eigen::Vector3f(1,1,1), 0.125, Eigen::Vector4f(1,0.5,0,1), nyx::plot<float>::Layer7 );
    s_plot.setPointSize( 5 );
    fuzzyCube( Eigen::Vector3f(0,0,0), 0.125, Eigen::Vector4f(0,0,0,1), nyx::plot<float>::Layer0 );
    fuzzyCube( Eigen::Vector3f(1,0,0), 0.125, Eigen::Vector4f(1,0,0,1), nyx::plot<float>::Layer1 );
    fuzzyCube( Eigen::Vector3f(0,1,0), 0.125, Eigen::Vector4f(0,1,0,1), nyx::plot<float>::Layer2 );
    fuzzyCube( Eigen::Vector3f(0,0,1), 0.125, Eigen::Vector4f(0,0,1,1), nyx::plot<float>::Layer3 );

    fuzzyAffines();
    alignedAffines();

    // Enter GLUT main loop. Main loop will be terminated only
    // on user request by exit(0). Other means do not currently exist in GLUT.
    glutMainLoop();

    return 0;
}

