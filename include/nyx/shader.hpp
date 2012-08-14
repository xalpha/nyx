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

#include <GL/glew.h>

#include <GL/glew.h>


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
    none,
    vertex=GL_VERTEX_SHADER,
    fragment=GL_FRAGMENT_SHADER,
    geometry=GL_GEOMETRY_SHADER_ARB
};


template<shader_type T>
class shader
{
public:
    shader();
    virtual ~shader();

    unsigned int id();

    void load( const std::string &src );

    bool is_loaded();

protected:
    // program
    std::string m_src;
    unsigned int m_id;
};


/////
// Implementation
///
template<shader_type T>
inline shader<T>::shader()
{
    // create the shader
    m_id = glCreateShader(T);
}


template<shader_type T>
inline shader<T>::~shader()
{
    glDeleteShader(m_id);
}


template<shader_type T>
inline unsigned int shader<T>::id()
{
    return m_id;
}


template<shader_type T>
inline void shader<T>::load( const std::string &src )
{
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
inline bool shader<T>::is_loaded()
{
    return m_src.size() > 0;
}


/////
// shader::None
///
template<>
class shader<none>
{
public:
    shader(){}
    virtual ~shader(){}

    unsigned int id(){ return 0; }
    void load( const std::string &src ){}
    bool is_loaded(){ return false; }
};


} // end namespace nyx
