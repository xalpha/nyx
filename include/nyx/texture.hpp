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
#include <iostream>

#include <nyx/util.hpp>

namespace nyx
{

/*
 * texture.h
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

    void setFormats( unsigned int internalFormat, unsigned int externalFormat );

    void setData( unsigned int width, const T *pixels=0 );
    void setData( unsigned int width, unsigned int height, const T *pixels=0 );
    void setData( unsigned int width, unsigned int height, unsigned int depth, const T *pixels=0 );

    void update( const T *pixels );
    void update();

    void bind();
    void unbind();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getDepth() const;

    unsigned int getInternalFormat() const;
    unsigned int getExternalFormat() const;
    unsigned int getIdentifier() const;

protected:
    void initTexture();
    static unsigned int getChannelCount( unsigned int format );

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
inline void texture<T>::setData( unsigned int width, const T *pixels )
{
    m_pixels = pixels;
    m_size[0] = width;
    m_size[1] = 1;
    m_size[2] = 1;
    m_type = GL_TEXTURE_1D;

    initTexture();
}


template <typename T>
inline void texture<T>::setData( unsigned int width, unsigned int height, const T *pixels )
{
    m_pixels = pixels;
    m_size[0] = width;
    m_size[1] = height;
    m_size[2] = 1;
    m_type = GL_TEXTURE_2D;

    initTexture();
}


template <typename T>
inline void texture<T>::setData( unsigned int width, unsigned int height, unsigned int depth, const T *pixels )
{
    m_pixels = pixels;
    m_size[0] = width;
    m_size[1] = height;
    m_size[2] = depth;
    m_type = GL_TEXTURE_3D;

    initTexture();
}


template <typename T>
inline void texture<T>::setFormats( unsigned int internalFormat, unsigned int externalFormat )
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
        std::size_t length = m_size[0]*m_size[1]*m_size[2]*getChannelCount(m_externalFormat);
        pixels = new T[ length ];
        m_pixels = pixels;
        for( size_t i=0; i<length; i++ )
            pixels[i]=0;
    }

    // bind the texture
    bind();

    // load the texture to the GPU
    switch(m_type)
    {
        case GL_TEXTURE_1D :
            glTexImage1D (m_type, 0, m_internalFormat, m_size[0], 0, m_externalFormat, util::Type<T>::getGL(), m_pixels);
            break;

        case GL_TEXTURE_2D :
            glTexImage2D (m_type, 0, m_internalFormat, m_size[0], m_size[1], 0, m_externalFormat, util::Type<T>::getGL(), m_pixels);
            break;

        case GL_TEXTURE_3D :
            glTexImage3D (m_type, 0, m_internalFormat, m_size[0], m_size[1], m_size[2], 0, m_externalFormat, util::Type<T>::getGL(), m_pixels);
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
inline void texture<T>::initTexture()
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
inline unsigned int texture<T>::getWidth() const
{
    return m_size[0];
}


template<typename T>
inline unsigned int texture<T>::getHeight() const
{
    return m_size[1];
}


template<typename T>
inline unsigned int texture<T>::getDepth() const
{
    return m_size[2];
}


template<typename T>
inline unsigned int texture<T>::getInternalFormat() const
{
    return m_internalFormat;
}


template<typename T>
inline unsigned int texture<T>::getExternalFormat() const
{
    return m_externalFormat;
}


template<typename T>
inline unsigned int texture<T>::getIdentifier() const
{
    return m_identifier;
}


template<typename T>
inline unsigned int texture<T>::getChannelCount( unsigned int format )
{
    switch( format )
    {
        case GL_COLOR_INDEX : 		return 1; break;
        case GL_RED :  				return 1; break;
        case GL_GREEN :  			return 1; break;
        case GL_BLUE :  			return 1; break;
        case GL_ALPHA :  			return 1; break;
        case GL_INTENSITY : 		return 1; break;
        case GL_RGB : 				return 3; break;
        case GL_BGR : 				return 3; break;
        case GL_RGBA : 				return 4; break;
        case GL_BGRA : 				return 4; break;
        case GL_LUMINANCE : 		return 1; break;
        case GL_LUMINANCE_ALPHA :	return 2; break;
        case GL_DEPTH_COMPONENT :	return 1; break;
    }
}


}

