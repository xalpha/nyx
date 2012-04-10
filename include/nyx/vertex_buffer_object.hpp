 ///////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of nyxGL, a lightweight C++ template library for OpenGL  //
//                                                                            //
// Copyright (C) 2010, 2011 Alexandru Duliu                                   //
//                                                                            //
// nyxGL is free software; you can redistribute it and/or                     //
// modify it under the terms of the GNU Lesser General Public                 //
// License as published by the Free Software Foundation; either               //
// version 3 of the License, or (at your option) any later version.           //
//                                                                            //
// nyxGL is distributed in the hope that it will be useful, but WITHOUT ANY   //
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS  //
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the //
// GNU General Public License for more details.                               //
//                                                                            //
// You should have received a copy of the GNU Lesser General Public           //
// License along with nyxGL. If not, see <http://www.gnu.org/licenses/>.      //
//                                                                            //
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GL/glew.h>

#include <nyx/exception.hpp>
#include <nyx/util.hpp>

#include <nyx/buffer/vertex_array_buffer.hpp>
#include <nyx/buffer/normal_array_buffer.hpp>
#include <nyx/buffer/color_array_buffer.hpp>
#include <nyx/buffer/texcoord_array_buffer.hpp>
#include <nyx/buffer/element_buffer.hpp>

namespace nyx
{

/*
 * vertex_buffer_object.h
 *
 *  Created on: May 4, 2010
 *      Author: alex
 *
 *      T - defines the type of the data used (float, double...)
 *      type - defines the usage of the usage of the array buffer (GL_VERTEX_ARRAY, GL_NORMAL_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY)
 *      size - how many components does the buffer have per element
 *      usage - used of memory optimizations
 *              (GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY)
 *              (GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY)
 *              (GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY)
 */


template <typename Ta=float, typename Te=unsigned int>
class vertex_buffer_object {
public:
    vertex_buffer_object();
    virtual ~vertex_buffer_object();

    void configure( unsigned int vertexSize, unsigned int colorSize, unsigned int texCoordSize, unsigned int primitiveType, unsigned int usage=GL_STATIC_DRAW );
    void configure( unsigned int primitiveType, unsigned int usage=GL_STATIC_DRAW );

    void initVertices( const Ta *vertices, unsigned int count );
    void initNormals( const Ta *vertices);
    void initColors( const Ta *vertices);
    void initTexCoords( const Ta *vertices);
    void initElements( const Te *elements, unsigned int count );

    void updateVertices( const Ta *vertices );
    void updateVertices();

    void updateNormals( const Ta *normals );
    void updateNormals();

    void updateColors( const Ta *colors );
    void updateColors();

    void updateTexCoords( const Ta *texCoords );
    void updateTexCoords();

    void updateElements( const Te *elements );
    void updateElements();

    void update();

    void draw();

protected:
    // array buffers GL_VERTEX_ARRAY, GL_NORMAL_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
    vertex_array_buffer<Ta> m_vertices;
    normal_array_buffer<Ta> m_normals;
    color_array_buffer<Ta> m_colors;
    texcoord_array_buffer<Ta> m_texCoords;

    // element buffer
    element_buffer<Te> m_elements;
};


template <typename Ta, typename Te>
inline vertex_buffer_object<Ta, Te>::vertex_buffer_object()
{
}


template <typename Ta, typename Te>
inline vertex_buffer_object<Ta, Te>::~vertex_buffer_object()
{
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::configure( unsigned int vertexSize, unsigned int colorSize, unsigned int texCoordSize, unsigned int primitiveType, unsigned int usage )
{
    m_vertices.configure(vertexSize, usage);
    m_normals.configure(3, usage);
    m_colors.configure(colorSize, usage);
    m_texCoords.configure(texCoordSize, usage);

    m_elements.configure(primitiveType, usage);
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::configure( unsigned int primitiveType, unsigned int usage )
{
    configure(3, 3, 2, primitiveType, usage);
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::initVertices( const Ta *vertices, unsigned int count )
{
    m_vertices.init(vertices, count);
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::initNormals( const Ta *normals)
{
    if( m_vertices.getCount() > 0 )
    {
        m_normals.init(normals, m_vertices.getCount());
    }
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::initColors( const Ta *colors)
{
    if( m_vertices.getCount() > 0 )
    {
        m_colors.init(colors, m_vertices.getCount());
    }
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::initTexCoords( const Ta *texCoords)
{
    if( m_vertices.getCount() > 0 )
    {
        m_texCoords.init(texCoords, m_vertices.getCount());
    }
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::initElements( const Te *elements, unsigned int count )
{
    m_elements.init(elements, count);
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateVertices( const Ta *vertices){ m_vertices.update(vertices); }
template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateVertices(){ m_vertices.update(); }

template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateNormals( const Ta *normals){ m_normals.update(normals); }
template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateNormals(){ m_normals.update(); }

template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateColors( const Ta *colors){ m_colors.update(colors); }
template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateColors(){ m_colors.update(); }

template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateTexCoords( const Ta *texCoords){ m_texCoords.update(texCoords); }
template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateTexCoords(){ m_texCoords.update(); }

template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateElements( const Te *elements){ m_elements.update(elements); }
template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::updateElements(){ m_elements.update(); }

template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::update()
{
    updateVertices();
    updateNormals();
    updateColors();
    updateTexCoords();
updateElements();
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::draw()
{
    if( m_vertices.isValid() )
        m_vertices.bind();
    else
        return;

    if( m_normals.isValid() )
        m_normals.bind();

    if( m_colors.isValid() )
        m_colors.bind();

    if( m_texCoords.isValid() )
        m_texCoords.bind();

    if( m_elements.isValid() )
    {
        m_elements.bind();
        glDrawElements( m_elements.getPrimitiveType(), m_elements.getCount()*m_elements.getSize(), util::type<Te>::getGL(), 0 );
    }
    else
        glDrawArrays( m_elements.getPrimitiveType(), 0, m_vertices.getCount());

    m_vertices.unbind();
    m_normals.unbind();
    m_colors.unbind();
    m_texCoords.unbind();
    m_elements.unbind();
}


} // end namespace nyx



