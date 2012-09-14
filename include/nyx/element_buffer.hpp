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

#include <nyx/buffer.hpp>

namespace nyx
{

/*
 * element_buffer.hpp
 *
 *  Created on: May 4, 2010
 *      Author: alex
 *
 */


template <typename T>
class element_buffer : public buffer<T>
{
public:
    element_buffer();

    virtual void set_components( unsigned int components );

    unsigned int getPrimitiveType();

protected:
    unsigned int m_type;  // primitive type
};


template <typename T>
inline element_buffer<T>::element_buffer() : buffer<T>::buffer()
{
    element_buffer<T>::m_target = GL_ELEMENT_ARRAY_BUFFER;
    m_type = 0;

    // check data type
    if( !util::type<T>::is_integer() )
        throw nyx::illegal_template_parameter("nyx::element_buffer::element_buffer: data type not supported.");
}


template <typename T>
inline void element_buffer<T>::set_components( unsigned int components )
{
    // check if the componets - here size are compatible with the buffer (here primitive type)
    switch( components )
    {
        case GL_POINTS :    element_buffer<T>::m_size = 1; break;
        case GL_LINES :     element_buffer<T>::m_size = 2; break;
        case GL_TRIANGLES : element_buffer<T>::m_size = 3; break;
        case GL_QUADS :     element_buffer<T>::m_size = 4; break;

        default:
            throw invalid_parameter("nyx::element_buffer::configure: unsupported element primitive.");
    }
    m_type = components;
}


template <typename T>
inline unsigned int element_buffer<T>::getPrimitiveType()
{
    return m_type;
}


} // end namespace nyx



