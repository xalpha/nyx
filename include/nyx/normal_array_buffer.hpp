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
 * normal_array_buffer.hpp
 *
 *  Created on: May 4, 2010
 *      Author: alex
 *
 */


template <typename T>
class normal_array_buffer : public array_buffer<T>
{
public:
    normal_array_buffer();

    virtual void set_components( unsigned int components );

    virtual void bind();
};


template <typename T>
inline normal_array_buffer<T>::normal_array_buffer() : array_buffer<T>::array_buffer()
{
    normal_array_buffer<T>::m_state = GL_NORMAL_ARRAY;

    // check if the type is compatible
    if( !util::type<T>::is_signed() )
        throw nyx::illegal_template_parameter("nyx::normal_array_buffer::normal_array_buffer: normal buffer does not support unsigned data types.");
}

template <typename T>
inline void normal_array_buffer<T>::set_components( unsigned int components )
{
    // check if the componets - here size are compatible with the buffer
    if( components != 3 )
        throw invalid_parameter("nyx::normal_array_buffer::setComponents: unsupported normal buffer size.");
    else
        normal_array_buffer<T>::m_size = components;
}


template <typename T>
inline void normal_array_buffer<T>::bind()
{
    buffer<T>::bind();
    glNormalPointer(util::type<T>::GL(), 0, 0 );
}


} // end namespace nyx



