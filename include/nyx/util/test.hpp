////////////////////////////////////////////////////////////////////////////////
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

#include <iostream>
#include <sstream>

#include <nyx/buffer.hpp>
#include <nyx/exception.hpp>


namespace nyx
{

/*
 * test.hpp
 *
 *  Created on: May 4, 2012
 *      Author: alex
 */


template <typename T>
inline std::string to_string( T val )
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

#ifdef __GNUC__
#define nyx_assert( expression ) if((expression)) ; else throw std::runtime_error( std::string("Assertion Failed: \"") + \
                                                                                   std::string( #expression ) + "\" in \"" + \
                                                                                   std::string( __func__ ) + "\" (\"" + \
                                                                                   std::string( __FILE__ ) + "\" on line " + \
                                                                                   nyx::to_string( __LINE__ ) + ").");
#else
#define nyx_assert( expression ) if((expression)) ; else throw std::runtime_error( std::string("Assertion Failed: \"") + \
                                                                                   std::string( #expression ) + "\" " + \
                                                                                   std::string( __FILE__ ) + " line " + \
                                                                                   std::string( "__LINE__" ) + ".");
#endif

} // end namespace nyx
