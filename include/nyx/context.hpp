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

#include <nyx/util.hpp>


namespace nyx
{

/*
 * context.h
 *
 *  Created on: Sep 14, 2012
 *      Author: alex
 */

template <typename T=GLuint>
class context
{
public:
    context();
    ~context();

    void init();

    bool ok();

    void status();

    T version();


protected:

    bool is_extension_supported( const std::string& str );

    void print_extension_support( const std::string& str );

protected:
    bool m_initialized;

}; // context


/////
// Implementation
///

template <typename T>
inline context<T>::context() :
    m_initialized(false)
{}


template <typename T>
inline context<T>::~context()
{}


template <typename T>
inline void context<T>::init()
{
    // init GLEW
    T err = glewInit();
    m_initialized = GLEW_OK == err;
    if( !m_initialized )
    {
        std::stringstream stream;
        stream << "nyx::context::init: GLEW error: \"";
        stream << glewGetErrorString(err);
        stream << "\".";
        throw std::runtime_error( stream.str() );
    }
}


template <typename T>
inline bool context<T>::ok()
{
    return m_initialized;
}


template <typename T>
inline void context<T>::status()
{
    if( m_initialized )
    {
        // adapter and driver information
        std::cout << "VENDOR = " << glGetString( GL_VENDOR ) << std::endl;
        std::cout << "RENDERER = " << glGetString( GL_RENDERER ) << std::endl;
        std::cout << "VERSION = " << glGetString( GL_VERSION ) << std::endl;

        // opengl version
        print_extension_support("GL_VERSION_1_1");
        print_extension_support("GL_VERSION_1_2");
        print_extension_support("GL_VERSION_1_3");
        print_extension_support("GL_VERSION_1_4");
        print_extension_support("GL_VERSION_1_5");
        print_extension_support("GL_VERSION_2_0");
        print_extension_support("GL_VERSION_2_1");
        print_extension_support("GL_VERSION_3_0");
        print_extension_support("GL_VERSION_3_1");
        print_extension_support("GL_VERSION_3_2");
        print_extension_support("GL_VERSION_4_0");
        print_extension_support("GL_VERSION_4_1");
    }
    else
        throw std::runtime_error( "nyx::context::status: not initialized." );
}


template <typename T>
inline T context<T>::version()
{
    if( m_initialized )
    {
        // init stuff
        T ver = GL_NONE;

        // check all opengl versions
        ver = is_extension_supported("GL_VERSION_1_1") ? 11 : ver;
        ver = is_extension_supported("GL_VERSION_1_2") ? 12 : ver;
        ver = is_extension_supported("GL_VERSION_1_3") ? 13 : ver;
        ver = is_extension_supported("GL_VERSION_1_4") ? 14 : ver;
        ver = is_extension_supported("GL_VERSION_1_5") ? 15 : ver;
        ver = is_extension_supported("GL_VERSION_2_0") ? 20 : ver;
        ver = is_extension_supported("GL_VERSION_2_1") ? 21 : ver;
        ver = is_extension_supported("GL_VERSION_3_0") ? 30 : ver;
        ver = is_extension_supported("GL_VERSION_3_1") ? 31 : ver;
        ver = is_extension_supported("GL_VERSION_3_2") ? 32 : ver;
        ver = is_extension_supported("GL_VERSION_4_0") ? 40 : ver;
        ver = is_extension_supported("GL_VERSION_4_1") ? 41 : ver;

        return ver;
    }
    else
        throw std::runtime_error( "nyx::context::status: not initialized." );
}


template <typename T>
inline bool context<T>::is_extension_supported( const std::string& str )
{
    GLenum err = glewIsSupported( str.c_str() );
    return GLEW_OK == err;
}


template <typename T>
inline void context<T>::print_extension_support( const std::string& str )
{
    std::cout << str;
    if( is_extension_supported( str.c_str() ) )
        std::cout << " = OK" << std::endl;
    else
        std::cout << " = MISSING" << std::endl;
}



} // end namespace nyx
