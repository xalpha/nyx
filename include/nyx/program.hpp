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

#include <string>

#include <nyx/shader.hpp>

namespace nyx
{

/*
 * program.h
 *
 *  Created on: May 22, 2010
 *      Author: alex
 */


template<shader_type V, shader_type F, shader_type G>
class program
{
public:
    program();
    virtual ~program();

    void load( const std::string &src, shader_type type );

    void enable();
    void disable();

protected:
    void link();

    void printProgramInfo();

protected:
    // program
    unsigned int m_id;
    bool m_loaded;

    Shader<V> m_vertexShader;
    Shader<F> m_fragmentShader;
    Shader<G> m_geometryShader;
};



/////
// Implementations
///
template<shader_type V, shader_type F, shader_type G>
inline program<V,F,G>::program()
{
    // check if the template parameters were set correctly
    if( V != vertex || F != fragment || (G != geometry && G != none) )
        throw std::runtime_error("nyx::program::program: improper template initialization");

    m_id = glCreateProgram();
}


template<shader_type V, shader_type F, shader_type G>
inline program<V,F,G>::~program()
{
    glDeleteProgram(m_id);
}


template<shader_type V, shader_type F, shader_type G>
inline void program<V,F,G>::load( const std::string &src, shader_type type )
{
    switch( type )
    {
        case vertex : m_vertexShader.load(src); break;
        case fragment : m_fragmentShader.load(src); break;
        case geometry : m_geometryShader.load(src); break;
        default : throw std::runtime_error("program::load: unsupported shader type"); break;
    }

    // check if all the source files are in
    bool loaded = true;
    loaded = loaded && m_vertexShader.isLoaded();
    loaded = loaded && m_fragmentShader.isLoaded();
    if( G == geometry )
    loaded = loaded && m_geometryShader.isLoaded();

    // if all here link
    if( loaded )
    {
        link();
        m_loaded = loaded;
    }
}


template<shader_type V, shader_type F, shader_type G>
inline void program<V,F,G>::enable()
{
    if(m_loaded)
        glUseProgram(m_id);
}


template<shader_type V, shader_type F, shader_type G>
inline void program<V,F,G>::disable()
{
    glUseProgram(0);
}


template<shader_type V, shader_type F, shader_type G>
inline void program<V,F,G>::link()
{
    // attach shaders
    glAttachShader(m_id, m_vertexShader.getID());
    glAttachShader(m_id, m_fragmentShader.getID());
    if( G == geometry )
       glAttachShader(m_id, m_geometryShader.getID());

    // link everything
    glLinkProgram(m_id);

    // validate Program
    //glValidateProgram(m_id);

    printProgramInfo();
}


template<shader_type V, shader_type F, shader_type G>
inline void program<V,F,G>::printProgramInfo()
{
    int logLength = 0;
    glGetObjectParameterivARB(m_id, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
    if (logLength > 0)
    {
        char *logText = new char[logLength];
        int writtenLength = 0;

        glGetInfoLogARB(m_id, logLength, &writtenLength, logText);

        std::cout << logText << std::endl;

        delete [] logText;
    }
}


typedef program<vertex, fragment, geometry> ShaderProgram;



} // end namespace nyx
