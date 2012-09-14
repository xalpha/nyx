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


namespace nyx
{

/*
 * buffer.hpp
 *
 *  Created on: May 22, 2010
 *      Author: alex
 *
 *      T - defines the type of the data used (float, double...)
 *      target - target to map the buffer (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER)
 *      state - defines the usage of the usage of the buffer (GL_VERTEX_ARRAY, GL_NORMAL_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY, ...)
 *      size - how many components does the buffer have per element
 *      type - primitive type
 *      usage - used of memory optimizations
 *              (GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY)
 *              (GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY)
 *              (GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY)
 */


template <typename T>
class buffer
{
public:
    buffer();
    virtual ~buffer();

    void configure( unsigned int components, unsigned int usage=GL_STATIC_DRAW );

    void init( const T *buf, unsigned int count );

    void update( const T *buf, unsigned int count, unsigned int offset );
    void update( const T *buf );
    void update();

    virtual void bind();
    virtual void unbind();

    unsigned int id();
    unsigned int count();
    unsigned int size();
    bool is_valid();

protected:
    virtual void set_components( unsigned int components ) = 0;
    void set_usage( unsigned int usage );

    void set_size( unsigned int size );
    void set_target( unsigned int target );
    void set_state( unsigned int state );


protected:
    const T *m_buffer;
    unsigned int m_count;
    unsigned int m_size;

    unsigned int m_identifier;
    unsigned int m_target;
    unsigned int m_state;
    unsigned int m_usage;

    bool m_configured;
    bool m_initialized;
    bool m_valid;
};


template <typename T>
inline buffer<T>::buffer()
{
    m_buffer = 0;
    m_count = 0;
    m_size = 0;

    m_identifier = 0;
    m_target = 0;
    m_state = 0;
    m_usage = 0;

    m_configured = false;
    m_valid = false;
}


template <typename T>
inline buffer<T>::~buffer()
{
    if( m_valid )
    {
        glDeleteBuffers( 1, &m_identifier);
    }
}

template <typename T>
inline void buffer<T>::configure( unsigned int components, unsigned int usage )
{
    set_components(components);
    set_usage(usage);
    m_configured = true;
}


template <typename T>
inline void buffer<T>::init( const T *buf, unsigned int count )
{
    if( m_configured )
    {
        m_buffer = buf;
        m_count = count;

        // delete old content if present
        if( m_valid )
        {
            glDeleteBuffers( 1, &m_identifier);
            m_valid = false;
        }

        // generate new buffer
        glGenBuffers( 1, &m_identifier);

        // update contents
        update();
    }
}


template <typename T>
inline void buffer<T>::update( const T *buf, unsigned int count, unsigned int offset)
{
    if( m_valid )
    {
        m_buffer = buf;
        glBindBuffer( m_target, m_identifier);
        glBufferSubData( m_target, offset, count*sizeof(T)*m_size, m_buffer);
        glBindBuffer( m_target, 0);
    }
}


template <typename T>
inline void buffer<T>::update( const T *buf )
{
    m_buffer = buf;
    update();
}


template <typename T>
inline void buffer<T>::update()
{
    if( m_identifier != 0 )
    {
        glBindBuffer( m_target, m_identifier);
        glBufferData( m_target, m_count*sizeof(T)*m_size, m_buffer, m_usage);
        glBindBuffer( m_target, 0);
        m_valid = true;
    }
}


template <typename T>
inline void buffer<T>::bind()
{
    glEnableClientState( m_state );
    glBindBuffer( m_target, m_identifier);
}


template <typename T>
inline void buffer<T>::unbind()
{
    glEnableClientState( m_state );
    glBindBuffer( m_target, 0);
    glDisableClientState( m_state );
}


template <typename T>
inline unsigned int buffer<T>::id()
{
    return m_identifier;
}


template <typename T>
inline unsigned int buffer<T>::count()
{
    return m_count;
}


template <typename T>
inline unsigned int buffer<T>::size()
{
    return m_size;
}


template <typename T>
inline bool buffer<T>::is_valid()
{
    return m_valid;
}


template <typename T>
inline void buffer<T>::set_usage( unsigned int usage )
{
    // check the buffer usage
    switch( usage )
    {
        case GL_STREAM_DRAW :
        case GL_STREAM_READ :
        case GL_STREAM_COPY :
        case GL_STATIC_DRAW :
        case GL_STATIC_READ :
        case GL_STATIC_COPY :
        case GL_DYNAMIC_DRAW :
        case GL_DYNAMIC_READ :
        case GL_DYNAMIC_COPY :
            m_usage = usage;
            break;

        default:
            throw invalid_parameter("nyx::buffer::setUsage: unsupported buffer usage.");
    }
}


template <typename T>
inline void buffer<T>::set_size( unsigned int size )
{
    m_size = size;
}

template <typename T>
inline void buffer<T>::set_target( unsigned int target )
{
    m_target = target;
}

template <typename T>
inline void buffer<T>::set_state( unsigned int state )
{
    m_state = state;
}



}
