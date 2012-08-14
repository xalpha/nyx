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

#include <nyx/array_buffer.hpp>

namespace nyx
{

/*
 * color_array_buffer.hpp
 *
 *  Created on: May 4, 2010
 *      Author: alex
 *
 */


template <typename T>
class color_array_buffer : public array_buffer<T>
{
public:
    color_array_buffer();

    virtual void set_components( unsigned int components );

    virtual void bind();
};


template <typename T>
inline color_array_buffer<T>::color_array_buffer() : array_buffer<T>::array_buffer()
{
    color_array_buffer<T>::m_state = GL_COLOR_ARRAY;

    // check if the type is compatible
    if( !util::type<T>::is_GL_compatible() )
        throw nyx::illegal_template_parameter("nyx::color_array_buffer::color_array_buffer: color buffer only supports GL-compatible data types.");
}

template <typename T>
inline void color_array_buffer<T>::set_components( unsigned int components )
{
    // check if the componets - here size are compatible with the buffer
    if( components <3 || components >4  )
        throw invalid_parameter("nyx::color_array_buffer::configure: unsupported color buffer size.");
    else
        color_array_buffer<T>::m_size = components;
}


template <typename T>
inline void color_array_buffer<T>::bind()
{
    buffer<T>::bind();
    glColorPointer( color_array_buffer<T>::m_size, util::type<T>::GL(), 0, 0 );
}


} // end namespace nyx



