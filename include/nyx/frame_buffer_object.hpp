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
#include <nyx/texture.hpp>


namespace nyx
{

/*
 * frame_buffer_objects.hpp
 *
 *  Created on: June 28, 2010
 *      Author: alex
 */


// TODO: add convert function just like the VBO (take care not to have two frame_buffer_objects identifiers)
// TODO: test functionality
template <typename T>
class frame_buffer_objects {
public:
    frame_buffer_objects();
    virtual ~frame_buffer_objects();

    void init();

    void attach_color_texture( unsigned int colorTex, unsigned int width, unsigned int height, bool keepDepthBuffer=false );
    void attach_depth_texture( unsigned int depthTex, unsigned int width, unsigned int height, bool keepColorBuffer=false );
    void attach_textures( unsigned int colorTex, unsigned int depthTex );

    void attach_color_texture( const nyx::texture<T> &colorTex );
    void attach_depth_texture( const nyx::texture<T> &depthTex );
    void attach_textures( const nyx::texture<T> &colorTex, const nyx::texture<T> &depthTex );

    void enable();
    void disable();

    void clear();

protected:
    void check();
    void clean_up( bool keepColorBuffer=false, bool keepDepthBuffer=false );

protected:
    bool m_initialized;
    unsigned int m_id;

    // textures
    unsigned int m_colorTex;
    unsigned int m_depthTex;

    // buffers
    unsigned int m_colorBuffer;
    unsigned int m_depthBuffer;
};


/////
// Implementation
///
template<typename T>
inline frame_buffer_objects<T>::frame_buffer_objects() :
    m_initialized(0),
    m_id(0),
    m_colorTex(0),
    m_depthTex(0),
    m_colorBuffer(0),
    m_depthBuffer(0)
{
}


template<typename T>
inline frame_buffer_objects<T>::~frame_buffer_objects()
{
    clean_up();
    glGenFramebuffersEXT( 1, &m_id );
}


template<typename T>
inline void frame_buffer_objects<T>::init()
{
    // init FBO
    if( !m_initialized )
    {
        glGenFramebuffersEXT( 1, &m_id );
        m_initialized = true;
    }
}


template<typename T>
inline void frame_buffer_objects<T>::attach_color_texture( unsigned int colorTex, unsigned int width, unsigned int height, bool keepDepthBuffer )
{
    // make sure we are initialized
    init();

    if( colorTex != 0 )
    {
        // init stuff
        m_colorTex = colorTex;
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_id );
        clean_up( false, keepDepthBuffer );

        // enable rendering to attachment 0
        glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );
        glReadBuffer( GL_COLOR_ATTACHMENT0_EXT );

        // generate internal depth buffer for the color texture
        if( !keepDepthBuffer )
        {
            glGenRenderbuffersEXT( 1, &m_depthBuffer );
            glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_depthBuffer );
            glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT32_ARB, width, height );
            glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_depthBuffer );
            glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
        }

        // attach the color texture
        glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_colorTex, 0);

        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );

        // check that all is well
        check();
    }
    else
        throw std::runtime_error("frame_buffer_objects::attachColorTexture: texture identifier is zero");
}


template<typename T>
inline void frame_buffer_objects<T>::attach_depth_texture( unsigned int depthTex, unsigned int width, unsigned int height, bool keepColorBuffer )
{
    // make sure we are initialized
    init();

    if( depthTex != 0 )
    {
        // init stuff
        m_depthTex = depthTex;
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_id );
        clean_up( keepColorBuffer, false );

        // generate internal color buffer for the depth texture
        if( !keepColorBuffer )
        {
            glGenRenderbuffersEXT( 1, &m_colorBuffer );
            glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_colorBuffer );
            glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_RGBA, width, height );
            glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, m_colorBuffer );
            glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
            glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
        }

        // attach depth texture
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, m_depthTex, 0);

        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_id );

        // check that all is well
        check();
    }
    else
        throw std::runtime_error("frame_buffer_objects::attachDepthTexture: texture identifier is zero");
}


template<typename T>
inline void frame_buffer_objects<T>::attach_textures( unsigned int colorTex, unsigned int depthTex )
{
    // make sure we are initialized
    init();

    if( colorTex != 0 && depthTex != 0 )
    {
        // Bind the FBO and
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_id );
        clean_up();

        // attach color texture to it
        m_colorTex = colorTex;
        glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_colorTex, 0);
        glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );
        glReadBuffer( GL_COLOR_ATTACHMENT0_EXT );

        // attach depth texture to it
        m_depthTex = depthTex;
        glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, m_colorTex, 0);

        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );

        // check that all is well
        check();
    }
    else
        throw std::runtime_error("frame_buffer_objects::attachTextures: a texture identifier is zero");
}


template<typename T>
inline void frame_buffer_objects<T>::attach_color_texture( const nyx::texture<T> &colorTex )
{
    attach_color_texture( colorTex.id(), colorTex.width(), colorTex.height() );
}


template<typename T>
inline void frame_buffer_objects<T>::attach_depth_texture( const nyx::texture<T> &depthTex )
{
    attach_depth_texture( depthTex.id(), depthTex.width(), depthTex.height() );
}


template<typename T>
inline void frame_buffer_objects<T>::attach_textures( const nyx::texture<T> &colorTex, const nyx::texture<T> &depthTex )
{
    attach_textures( colorTex.id(), depthTex.id() );
}


template<typename T>
inline void frame_buffer_objects<T>::enable()
{
    // make sure we are initialized
    init();

    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_id );
    glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );
    glReadBuffer( GL_COLOR_ATTACHMENT0_EXT );
}


template<typename T>
inline void frame_buffer_objects<T>::disable()
{
    // make sure we are initialized
    init();

    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}


template<typename T>
inline void frame_buffer_objects<T>::clear()
{
    clean_up( true, true );
}


template<typename T>
inline void frame_buffer_objects<T>::clean_up(  bool keepColorBuffer, bool keepDepthBuffer )
{
    // make sure we are initialized
    init();

    if( m_colorBuffer != 0 && !keepColorBuffer )
        glDeleteRenderbuffersEXT( 1, &m_colorBuffer );
    if( m_depthBuffer != 0 && !keepDepthBuffer )
        glDeleteRenderbuffersEXT( 1, &m_depthBuffer );
}


template<typename T>
inline void frame_buffer_objects<T>::check()
{
    // make sure we are initialized
    init();

    // check if the FBO was setup properly
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_id );
    GLenum fboStatus = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
    std::string errors;
    switch( fboStatus )
    {
        //case GL_FRAMEBUFFER_COMPLETE_EXT                        : errors.append("GL_FRAMEBUFFER_COMPLETE_EXT\n"); break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT           : errors.append("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT\n"); break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT   : errors.append("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT\n"); break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT           : errors.append("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT\n"); break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT              : errors.append("GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT\n"); break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT          : errors.append("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT\n"); break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT          : errors.append("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT\n"); break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT                     : errors.append("GL_FRAMEBUFFER_UNSUPPORTED_EXT\n"); break;
        default : break;
    }

    if( errors.size() != 0 )
        throw nyx::opengl_error(errors.c_str());
}


} // namespace nyx
