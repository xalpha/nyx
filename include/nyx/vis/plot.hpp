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

#include <iostream>
#include <list>
#include <map>
#include <numeric>

#include <Eigen/Core>

#include <nyx/object/vertex_buffer_object.hpp>

#include <nyx/vis/widget.hpp>

/*
 *  plot.hpp
 *
 *  Created on: Aug 16, 2010
 *      Author: alex
 */


namespace nyx
{

template <typename T>
class plot : public widget<T>
{

protected:


public:
    typedef Eigen::Matrix<T,2,1> Vector2;
    typedef Eigen::Matrix<T,3,1> Vector3;
    typedef Eigen::Matrix<T,4,1> Vector4;
    typedef Eigen::Matrix<T,4,4> Matrix4;
    typedef nyx::vertex_buffer_object<T,unsigned int> VBO;

    static const size_t s_layerCount = 16;

    struct Model
    {
        T color;
        VBO buffer;
        T lineWidth;
        T pointSize;
        bool transparent;
    };

    typedef std::list< Model > ModelList;
    typedef std::vector<ModelList> LayerMap;

    // The flags define:
    // Colors:
    // What to draw
    // How to draw it
    enum Flags
    {
        Layer0    = 0x00000000,
        Layer1    = 0x00000001,
        Layer2    = 0x00000002,
        Layer3    = 0x00000003,
        Layer4    = 0x00000004,
        Layer5    = 0x00000005,
        Layer6    = 0x00000006,
        Layer7    = 0x00000007,
        Layer8    = 0x00000008,
        Layer9    = 0x00000009,
        Layer10   = 0x0000000A,
        Layer11   = 0x0000000B,
        Layer12   = 0x0000000C,
        Layer13   = 0x0000000D,
        Layer14   = 0x0000000E,
        Layer15   = 0x0000000F,
        Pos       = 0x00010000,
        CS        = 0x00020000,
        Center    = 0x00040000,
        Transparent = 0x00080000
    };



public:
    plot();

    virtual ~plot();

    void draw();

    void setColor( const Vector4& color );
    void setLineWidth( T width );
    void setPointSize( T size );

    template <typename R>
    void operator() ( const std::vector<Eigen::Matrix<R,3,1> > &points, uint32_t flags );

    template <typename R>
    void operator() ( const std::vector<Eigen::Matrix<R,3,1> > &points, const std::vector<Eigen::Matrix<R,4,1> > &colors, uint32_t flags );

    template <typename R>
    void operator() ( const Eigen::Matrix<R,4,4> &trans, uint32_t flags );

    template <typename R>
    void operator() ( const std::vector<Eigen::Matrix<R,4,4> > &trans, uint32_t flags );

    void clear();
    void clear( const uint32_t layer );


protected:
    void drawCS( float s );

    void addGeometry( const std::vector<T> &v, const std::vector<T> &c, uint32_t geometry, uint32_t flags );

    void updateCenter( const std::vector<T> &v );

protected:
    // VBO buffers
    LayerMap m_layers;

    // coordinate system
    std::vector<Vector3> m_cs_vertices;
    std::vector<Vector4> m_cs_colors;

    // states
    Vector4 m_color;
    T m_lineWidth;
    T m_pointSize;

    // min and max coords in volume
    Vector3 m_min;
    Vector3 m_max;
};


/////
// Implementation
///

template <typename T>
inline plot<T>::plot() :
    widget<T>(),
    m_layers(s_layerCount),
    m_color(0,0,0,1),
    m_lineWidth(1),
    m_pointSize(1)
{
    // init coordinate system geometry
    m_cs_vertices.push_back( Vector3(0,0,0) );
    m_cs_vertices.push_back( Vector3(1,0,0) );
    m_cs_vertices.push_back( Vector3(0,0,0) );
    m_cs_vertices.push_back( Vector3(0,1,0) );
    m_cs_vertices.push_back( Vector3(0,0,0) );
    m_cs_vertices.push_back( Vector3(0,0,1) );

    m_cs_colors.push_back( Vector4(1,0,0,1) );
    m_cs_colors.push_back( Vector4(1,0,0,1) );
    m_cs_colors.push_back( Vector4(0,1,0,1) );
    m_cs_colors.push_back( Vector4(0,1,0,1) );
    m_cs_colors.push_back( Vector4(0,0,1,1) );
    m_cs_colors.push_back( Vector4(0,0,1,1) );

    // init min
    m_min(0) = std::numeric_limits<T>::max();
    m_min(1) = std::numeric_limits<T>::max();
    m_min(2) = std::numeric_limits<T>::max();

    // init max
    m_max(0) = std::numeric_limits<T>::min();
    m_max(0) = std::numeric_limits<T>::min();
    m_max(0) = std::numeric_limits<T>::min();

    // set background to white
    widget<T>::m_backgroundColor = Vector3(1,1,1);
}


template <typename T>
inline plot<T>::~plot(){}


template <typename T>
inline void plot<T>::draw()
{
    // clear buffer
    nyx::gl::ClearColor( nyx::widget<T>::m_backgroundColor );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the mvp matrix
    widget<T>::setView();

    // draw one big CS smack in the origin
    glLineWidth( 2.0f );
    drawCS(1.0f);
    glLineWidth( 1.5f );

    // draw all transformations
    for( size_t l=0; l != s_layerCount; l++ )
    {
        for( typename ModelList::iterator bufIt=m_layers[l].begin(); bufIt!=m_layers[l].end(); bufIt++ )
        {
            glDepthMask( static_cast<GLboolean>(!bufIt->transparent) );
            glLineWidth( static_cast<GLfloat>(bufIt->lineWidth) );
            glPointSize( static_cast<GLfloat>(bufIt->pointSize) );
            bufIt->buffer.draw();
            glDepthMask( GL_TRUE );
        }
    }
}


template <typename T>
inline void plot<T>::setColor( const Vector4& color )
{
    m_color = color;
}


template <typename T>
inline void plot<T>::setLineWidth( T width )
{
    m_lineWidth = width;
}


template <typename T>
inline void plot<T>::setPointSize( T size )
{
    m_pointSize = size;
}


template <typename T>
template <typename R>
inline void plot<T>::operator() ( const std::vector<Eigen::Matrix<R,3,1> > &points, uint32_t flags )
{
    // init stuff
    std::vector<T> pointsV;
    std::vector<T> pointsC;

    // color
    Vector4 col = m_color;

    for( size_t i=0; i<points.size(); i++ )
    {
        pointsV.push_back( static_cast<T>( points[i](0) ) );
        pointsV.push_back( static_cast<T>( points[i](1) ) );
        pointsV.push_back( static_cast<T>( points[i](2) ) );

        pointsC.push_back( col(0) );
        pointsC.push_back( col(1) );
        pointsC.push_back( col(2) );
        pointsC.push_back( col(3) );
    }

    addGeometry( pointsV, pointsC, GL_POINTS, flags );
}


template <typename T>
template <typename R>
inline void plot<T>::operator() ( const std::vector<Eigen::Matrix<R,3,1> > &points, const std::vector<Eigen::Matrix<R,4,1> > &colors, uint32_t flags )
{
    // init stuff
    std::vector<T> pointsV;
    std::vector<T> pointsC;

    for( size_t i=0; i<points.size(); i++ )
    {
        pointsV.push_back( static_cast<T>( points[i](0) ) );
        pointsV.push_back( static_cast<T>( points[i](1) ) );
        pointsV.push_back( static_cast<T>( points[i](2) ) );

        pointsC.push_back( static_cast<T>( colors[i](0) ) );
        pointsC.push_back( static_cast<T>( colors[i](1) ) );
        pointsC.push_back( static_cast<T>( colors[i](2) ) );
        pointsC.push_back( static_cast<T>( colors[i](3) ) );
    }

    addGeometry( pointsV, pointsC, GL_POINTS, flags );
}


template <typename T>
template <typename R>
inline void plot<T>::operator() ( const Eigen::Matrix<R,4,4> &trans, uint32_t flags )
{
    std::vector<Eigen::Matrix<R,4,4> > vec;
    vec.push_back( trans );
    plot::operator ()( vec, flags );
}


template <typename T>
template <typename R>
void plot<T>::operator() ( const std::vector<Eigen::Matrix<R,4,4> > &trans, uint32_t flags )
{
    // init stuff
    std::vector<T> pointsV;
    std::vector<T> pointsC;
    std::vector<T> linesV;
    std::vector<T> linesC;

    // color
    Vector4 col = m_color;

    for( size_t i=0; i<trans.size(); i++ )
    {
        // draw the Pos ?
        if( bool(flags & Pos) )
        {
            pointsV.push_back( static_cast<T>( trans[i](12) ) );
            pointsV.push_back( static_cast<T>( trans[i](13) ) );
            pointsV.push_back( static_cast<T>( trans[i](14) ) );

            pointsC.push_back( col(0) );
            pointsC.push_back( col(1) );
            pointsC.push_back( col(2) );
            pointsC.push_back( col(3) );
        }

        // draw the CS !?
        for( size_t j=0; bool(flags & CS) & (j<m_cs_vertices.size()); j++ )
        {
            Vector4 v( 0.1f*m_cs_vertices[j](0),
                       0.1f*m_cs_vertices[j](1),
                       0.1f*m_cs_vertices[j](2), 1 );
            v = trans[i].template cast<T>() * v;

            linesV.push_back( v(0) / v(3) );
            linesV.push_back( v(1) / v(3) );
            linesV.push_back( v(2) / v(3) );

            linesC.push_back( m_cs_colors[j](0) );
            linesC.push_back( m_cs_colors[j](1) );
            linesC.push_back( m_cs_colors[j](2) );
            linesC.push_back( m_color(3) );
        }
    }

    addGeometry( pointsV, pointsC, GL_POINTS, flags );
    addGeometry( linesV, linesC, GL_LINES, flags );
}


template <typename T>
inline void plot<T>::clear()
{
    for( size_t i=0; i<s_layerCount; i++ )
        m_layers[i].clear();
    m_min = Vector3::Zero();
    m_max = Vector3::Zero();
}


template <typename T>
inline void plot<T>::clear( const uint32_t layer )
{
    if( layer < s_layerCount )
        m_layers[layer].clear();
    else
        std::cerr << "nyx::plot::clear: layer \"" << layer << "\" not found." << std::endl;
}


template <typename T>
inline void plot<T>::drawCS( float s )
{
    glBegin( GL_LINES );
        for( size_t i=0; i<m_cs_vertices.size(); i++ )
        {
            nyx::gl::Color4( m_cs_colors[i].data() );
            nyx::gl::Vertex3( m_cs_vertices[i].data() );
        }
    glEnd();
}


template <typename T>
inline void plot<T>::addGeometry( const std::vector<T> &v, const std::vector<T> &c, uint32_t geometry, uint32_t flags )
{
    // get the layer
    uint32_t layer = flags & Layer15;

    // add the model
    m_layers[layer].push_back( Model() );
    m_layers[layer].back().buffer.configure( 3, 4, 2, geometry );
    m_layers[layer].back().buffer.initVertices( v.data(), v.size()/3 );
    m_layers[layer].back().buffer.initColors( c.data() );
    m_layers[layer].back().lineWidth = m_lineWidth;
    m_layers[layer].back().pointSize = m_pointSize;
    m_layers[layer].back().transparent = static_cast<bool>(flags & Transparent );

    // update the rotation center
    if( static_cast<bool>(flags & Center ) )
        updateCenter( v );
}


template <typename T>
inline void plot<T>::updateCenter( const std::vector<T> &v )
{
    // update min and max
    for( size_t i=0; i<v.size()/3; i++ )
    {
        for( size_t j=0; j<3; j++ )
        {
            m_min(j) = (v[i*3+j] < m_min(j)) ? v[i*3+j] : m_min(j);
            m_max(j) = (v[i*3+j] > m_max(j)) ? v[i*3+j] : m_max(j);
        }
    }

    // update center
    widget<T>::m_center = static_cast<T>(0.5) * (m_min + m_max);
}

} // namespace nyx
