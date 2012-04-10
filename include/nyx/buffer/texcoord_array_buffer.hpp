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

#include <nyx/buffer/array_buffer.hpp>

namespace nyx
{

/*
 * texcoord_array_buffer
 *
 *  Created on: May 4, 2010
 *      Author: alex
 *
 */


template <typename T>
class texcoord_array_buffer : public array_buffer<T>
{
public:
    texcoord_array_buffer();

    virtual void setComponents( unsigned int components );

    virtual void bind();
};


template <typename T>
inline texcoord_array_buffer<T>::texcoord_array_buffer() : array_buffer<T>::array_buffer()
{
    texcoord_array_buffer<T>::m_state = GL_TEXTURE_COORD_ARRAY;

    // check if the type is compatible
    if( util::type<T>::isUnsigned() || util::type<T>::getGL()==GL_BYTE )
        throw nyx::illegal_template_parameter("nyxGL::texcoord_array_buffer::texcoord_array_buffer: texCoods buffer does not support unsigned data types, as well as GL_BYTE.");
}

template <typename T>
inline void texcoord_array_buffer<T>::setComponents( unsigned int components )
{
    // check if the componets - here size are compatible with the buffer
    if( components <1 || components >4  )
        throw invalid_parameter("nyxGL::texcoord_array_buffer::setComponents: unsupported color buffer size.");
    else
        texcoord_array_buffer<T>::m_size = components;
}


template <typename T>
inline void texcoord_array_buffer<T>::bind()
{
    buffer<T>::bind();
    glTexCoordPointer( texcoord_array_buffer<T>::m_size, util::type<T>::getGL(), 0, 0 );
}


} // end namespace nyx



