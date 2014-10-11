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

#include <nyx/shader.hpp>

namespace nyx
{

/*
 * program.hpp
 *
 *  Created on: May 22, 2010
 *      Author: alex
 */


template<typename Ch>
class base_shader_program
{
public:
    base_shader_program();
    virtual ~base_shader_program();

    void init();

    void load( const std::basic_string<Ch> &src, shader_type type );
    void load_vertex_shader( const std::basic_string<Ch> &src );
    void load_fragment_shader( const std::basic_string<Ch> &src );
    void load_geometry_shader( const std::basic_string<Ch> &src );

    void enable();
    void disable();

protected:
    void link();

    void print_program_info();

protected:
    // program
    bool m_initialized;
    unsigned int m_id;
    bool m_loaded;

    geometry_shader m_vertexShader;
    fragment_shader m_fragmentShader;
    geometry_shader m_geometryShader;
};

typedef base_shader_program<char> shader_program;


/////
// Implementations
///
template<typename Ch>
inline base_shader_program<Ch>::base_shader_program() : m_initialized(true), m_id(0)
{
}


template<typename Ch>
inline base_shader_program<Ch>::~base_shader_program()
{
    if( m_initialized )
        glDeleteProgram(m_id);
}


template<typename Ch>
inline void base_shader_program<Ch>::init()
{
    if( !m_initialized )
    {
        m_id = glCreateProgram();
        m_initialized = true;
    }
}


template<typename Ch>
inline void base_shader_program<Ch>::load(const std::basic_string<Ch> &src, shader_type type )
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
    loaded = loaded && m_vertexShader.is_loaded();
    loaded = loaded && m_fragmentShader.is_loaded();

    // if all here link
    if( loaded )
    {
        link();
        m_loaded = loaded;
    }
}


template<typename Ch>
inline void base_shader_program<Ch>::load_vertex_shader( const std::basic_string<Ch> &src )
{
    load( src, nyx::vertex );
}


template<typename Ch>
inline void base_shader_program<Ch>::load_fragment_shader( const std::basic_string<Ch> &src )
{
    load( src, nyx::fragment );
}


template<typename Ch>
inline void base_shader_program<Ch>::load_geometry_shader( const std::basic_string<Ch> &src )
{
    load( src, nyx::geometry );
}


template<typename Ch>
inline void base_shader_program<Ch>::enable()
{
    if(m_loaded)
        glUseProgram(m_id);
}


template<typename Ch>
inline void base_shader_program<Ch>::disable()
{
    glUseProgram(0);
}


template<typename Ch>
inline void base_shader_program<Ch>::link()
{
    // attach shaders
    glAttachShader(m_id, m_vertexShader.id());
    glAttachShader(m_id, m_fragmentShader.id());
    if( m_geometryShader.is_loaded() )
       glAttachShader(m_id, m_geometryShader.id());

    // link everything
    glLinkProgram(m_id);

    // validate Program
    //glValidateProgram(m_id);

    print_program_info();
}


template<typename Ch>
inline void base_shader_program<Ch>::print_program_info()
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


} // end namespace nyx
