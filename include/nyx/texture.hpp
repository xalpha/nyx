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

#include <iostream>

#include <nyx/util.hpp>

namespace nyx
{

/*
 * texture.hpp
 *
 *  Created on: May 4, 2010
 *      Author: alex
 */



template <typename T>
class texture
{
public:
    texture();
    virtual ~texture();

    void set_format( unsigned int format );
    void set_format( unsigned int internalFormat, unsigned int externalFormat );

    void set_data( unsigned int width, const T *pixels );
    void set_data( unsigned int width, unsigned int height, const T *pixels );
    void set_data( unsigned int width, unsigned int height, unsigned int depth, const T *pixels );

    void update( const T *pixels );
    void update();

    void bind();
    void unbind();

    unsigned int width() const;
    unsigned int height() const;
    unsigned int depth() const;

    unsigned int internal_format() const;
    unsigned int external_format() const;
    unsigned int id() const;

protected:
    void init();

protected:
    // texture data
    const T *m_pixels;
    unsigned int m_size[3];


    // openGL relevant information
    unsigned int m_type;
    unsigned int m_internalFormat;
    unsigned int m_externalFormat;
    unsigned int m_identifier;
};


template <typename T>
inline texture<T>::texture()
{
    // init stuff
    m_pixels = 0;
    m_size[0] = m_size[1] = m_size[2] = 0;

    m_type = 0;
    m_internalFormat = GL_RGBA;
    m_externalFormat = GL_RGBA;
    m_identifier = 0;
}


template <typename T>
inline texture<T>::~texture()
{
    if( m_identifier != 0 )
    {
        glDeleteTextures( 1, &m_identifier );
    }
}


template <typename T>
inline void texture<T>::set_data( unsigned int width, const T *pixels )
{
    m_size[0] = width;
    m_size[1] = 1;
    m_size[2] = 1;
    m_pixels = pixels;
    m_type = GL_TEXTURE_1D;

    init();
}


template <typename T>
inline void texture<T>::set_data( unsigned int width, unsigned int height, const T *pixels )
{
    m_size[0] = width;
    m_size[1] = height;
    m_size[2] = 1;
    m_pixels = pixels;
    m_type = GL_TEXTURE_2D;

    init();
}


template <typename T>
inline void texture<T>::set_data( unsigned int width, unsigned int height, unsigned int depth, const T *pixels )
{
    m_size[0] = width;
    m_size[1] = height;
    m_size[2] = depth;
    m_type = GL_TEXTURE_3D;

    init();
}


template <typename T>
inline void texture<T>::set_format( unsigned int format )
{
    m_internalFormat = format;
    m_externalFormat = format;
}


template <typename T>
inline void texture<T>::set_format( unsigned int internalFormat, unsigned int externalFormat )
{
    m_internalFormat = internalFormat;
    m_externalFormat = externalFormat;
}


template <typename T>
inline void texture<T>::update( const T *pixels )
{
    m_pixels = pixels;
    update();
}


template <typename T>
inline void texture<T>::update()
{
    // if the pointer is 0 init with black
    bool noData = m_pixels == 0;
    T *pixels;
    if( noData )
    {
        std::size_t length = m_size[0]*m_size[1]*m_size[2]* util::channels( m_externalFormat );
        pixels = new T[ length ];
        m_pixels = pixels;
        for( size_t i=0; i<length; i++ )
            pixels[i]=0;
    }

    // set the row stride
    //glPixelStorei(GL_UNPACK_ROW_LENGTH,m_stride);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    // bind the texture
    bind();

    // load the texture to the GPU
    switch(m_type)
    {
        case GL_TEXTURE_1D :
            glTexImage1D ( m_type,
                           0,
                           m_internalFormat,
                           static_cast<GLsizei>(m_size[0]),
                           0,
                           m_externalFormat,
                           util::type<T>::GL(),
                           m_pixels );
            break;

        case GL_TEXTURE_2D :
            glTexImage2D ( m_type,
                           0,
                           m_internalFormat,
                           static_cast<GLsizei>(m_size[0]),
                           static_cast<GLsizei>(m_size[1]),
                           0,
                           m_externalFormat,
                           util::type<T>::GL(),
                           m_pixels );
            break;

        case GL_TEXTURE_3D :
            glTexImage3D ( m_type,
                           0,
                           m_internalFormat,
                           static_cast<GLsizei>(m_size[0]),
                           static_cast<GLsizei>(m_size[1]),
                           static_cast<GLsizei>(m_size[2]),
                           0,
                           m_externalFormat,
                           util::type<T>::GL(),
                           m_pixels);
            break;
    }

    // unbind the texture
    unbind();

    // clean up
    if( noData )
    {
        delete [] pixels;
        m_pixels = 0;
    }
}


template <typename T>
inline void texture<T>::bind()
{
    glBindTexture(m_type, m_identifier);
}


template <typename T>
inline void texture<T>::unbind()
{
    glBindTexture(m_type, 0);
}


template <typename T>
inline void texture<T>::init()
{
    // delete if necessary old texture
    if( m_identifier != 0 )
    {
        glDeleteTextures( 1, &m_identifier );
    }

    // allocate a texture name
    glGenTextures( 1, &m_identifier );

    // select our current texture
    bind();

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // setup bilinear interpolation
    glTexParameterf( m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    // clamp or repeat
    //glTexParameterf( type, GL_TEXTURE_WRAP_S, clamp ? GL_CLAMP : GL_REPEAT );
    //glTexParameterf( type, GL_TEXTURE_WRAP_T, clamp ? GL_CLAMP : GL_REPEAT );
    glTexParameterf( m_type, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( m_type, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glTexParameterf( m_type, GL_TEXTURE_WRAP_R, GL_CLAMP );

    // upload the texture
    update();

    // deselect the texture
    unbind();
}


template<typename T>
inline unsigned int texture<T>::width() const
{
    return m_size[0];
}


template<typename T>
inline unsigned int texture<T>::height() const
{
    return m_size[1];
}


template<typename T>
inline unsigned int texture<T>::depth() const
{
    return m_size[2];
}


template<typename T>
inline unsigned int texture<T>::internal_format() const
{
    return m_internalFormat;
}


template<typename T>
inline unsigned int texture<T>::external_format() const
{
    return m_externalFormat;
}


template<typename T>
inline unsigned int texture<T>::id() const
{
    return m_identifier;
}


}

