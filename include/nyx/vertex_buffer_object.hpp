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

#include <nyx/exception.hpp>
#include <nyx/util.hpp>

#include <nyx/vertex_array_buffer.hpp>
#include <nyx/normal_array_buffer.hpp>
#include <nyx/color_array_buffer.hpp>
#include <nyx/texcoord_array_buffer.hpp>
#include <nyx/element_buffer.hpp>

namespace nyx
{

/*
 * vertex_buffer_object.hpp
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
    void draw_vertices( unsigned int offset, unsigned int size );
    void draw_elements( unsigned int offset, unsigned int size );

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
    if( m_vertices.count() > 0 )
        m_normals.init(normals, m_vertices.count());
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::initColors( const Ta *colors)
{
    if( m_vertices.count() > 0 )
        m_colors.init(colors, m_vertices.count());
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::initTexCoords( const Ta *texCoords)
{
    if( m_vertices.count() > 0 )
        m_texCoords.init(texCoords, m_vertices.count());
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
    if( m_elements.is_valid() )
        draw_elements( 0, m_elements.count() );
    else
        draw_vertices( 0, m_vertices.count() );
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::draw_vertices( unsigned int offset, unsigned int size )
{
    // vertices
    if( m_vertices.is_valid() ) m_vertices.bind();
    else throw std::runtime_error( "vertex_buffer_object::draw_vertices: no vertices." );

    if( m_normals.is_valid() ) m_normals.bind();     // normals
    if( m_colors.is_valid() ) m_colors.bind();       // colors
    if( m_texCoords.is_valid() ) m_texCoords.bind(); // texture coordinates

    // elements
    if( m_elements.is_valid() ) throw std::runtime_error( "vertex_buffer_object::draw_vertices: elements are aleady defined, use \"draw_elements\" instead." );
    else glDrawArrays( m_elements.getPrimitiveType(), offset, size);

    // unbind
    m_vertices.unbind();
    m_normals.unbind();
    m_colors.unbind();
    m_texCoords.unbind();
    m_elements.unbind();
}


template <typename Ta, typename Te>
inline void vertex_buffer_object<Ta, Te>::draw_elements( unsigned int offset, unsigned int size )
{
    // vertices
    if( m_vertices.is_valid() ) m_vertices.bind();
    else throw std::runtime_error( "vertex_buffer_object::draw_elements: no vertices." );

    if( m_normals.is_valid() ) m_normals.bind();     // normals
    if( m_colors.is_valid() ) m_colors.bind();       // colors
    if( m_texCoords.is_valid() ) m_texCoords.bind(); // texture coordinates

    // elements
    if( m_elements.is_valid() )
    {
        m_elements.bind();
        glDrawElements( m_elements.getPrimitiveType(), m_elements.count()*m_elements.size(), util::type<Te>::GL(), 0 ); // TODO: there is still an issue here with the offset
    }
    else
        throw std::runtime_error( "vertex_buffer_object::draw_elements: there are no elements." );

    // unbind
    m_vertices.unbind();
    m_normals.unbind();
    m_colors.unbind();
    m_texCoords.unbind();
    m_elements.unbind();
}


} // end namespace nyx
