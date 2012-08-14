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
 * array_buffer.hpp
 *
 *  Created on: May 4, 2010
 *      Author: alex
 *
 */


template <typename T>
class array_buffer : public buffer<T>
{
public:
    array_buffer();

};


template <typename T>
inline array_buffer<T>::array_buffer() : buffer<T>::buffer()
{
    array_buffer<T>::m_target = GL_ARRAY_BUFFER;
}


} // end namespace nyx



