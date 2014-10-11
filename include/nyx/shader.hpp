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


#include <string>
#include <stdexcept>

#include <nyx/util.hpp>


namespace nyx
{

/*
 * shader.hpp
 *
 *  Created on: May 22, 2010
 *      Author: alex
 */

enum shader_type
{
    vertex=GL_VERTEX_SHADER,
    fragment=GL_FRAGMENT_SHADER,
    geometry=GL_GEOMETRY_SHADER_ARB
};


template<shader_type T>
class base_shader
{
public:
    base_shader();
    virtual ~base_shader();

    void init();

    unsigned int id();

    void load( const std::string &src );

    bool is_loaded();

protected:
    // program
    bool m_initialized;
    std::string m_src;
    unsigned int m_id;
};

typedef base_shader<vertex> vertex_shader;
typedef base_shader<fragment> fragment_shader;
typedef base_shader<geometry> geometry_shader;


/////
// Implementation
///
template<shader_type T>
inline base_shader<T>::base_shader() : m_initialized(false)
{
}


template<shader_type T>
inline base_shader<T>::~base_shader()
{
    glDeleteShader(m_id);
}


template<shader_type T>
inline void base_shader<T>::init()
{
    if( !m_initialized )
    {
        // create the shader
        m_id = glCreateShader(T);
        m_initialized = true;
    }
}


template<shader_type T>
inline unsigned int base_shader<T>::id()
{
    return m_id;
}


template<shader_type T>
inline void base_shader<T>::load( const std::string &src )
{
    // make sure we are initialized
    init();

    if( src.size() > 0 )
    {
        m_src = src;

        // pass on the source
        const char *tempChar = m_src.c_str();
        glShaderSource(m_id, 1, &tempChar, NULL);

        // compile the shader
        glCompileShader(m_id);
    }
    else
        throw std::runtime_error("shader::load: source string is empty");
}


template<shader_type T>
inline bool base_shader<T>::is_loaded()
{
    return m_src.size() > 0;
}


} // end namespace nyx
