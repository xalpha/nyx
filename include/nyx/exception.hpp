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

#include <stdexcept>

/*
 * Exceptions.hpp
 *
 *  Created on: May 4, 2010
 *      Author: alex
 */

namespace nyx
{

/// Exception class which is thrown if a template parameter is used with an illegal value
class illegal_template_parameter : public std::logic_error {
public:
    /// Constructor with exception message string.
    explicit illegal_template_parameter(const std::string& message) : std::logic_error(message) {}
};

/// Exception class which is thrown when a class has not been successfully initialized
class class_not_configured : public std::runtime_error {
public:
    /// Constructor with exception message string.
    explicit class_not_configured(const std::string& message) : std::runtime_error(message) {}
};

/// Exception class which is thrown if a function parameter is used with an illegal value
class invalid_parameter : public std::logic_error {
public:
    /// Constructor with exception message string.
    explicit invalid_parameter(const std::string& message) : std::logic_error(message) {}
};


/// Exception class which is thrown if a file is not found
class file_not_found : public std::runtime_error {
public:
    /// Constructor with exception message string.
    explicit file_not_found(const std::string& message) : std::runtime_error(message) {}
};


/// Exception class which is thrown if a file cannot be successfully loaded
class error_loading_file : public std::runtime_error {
public:
    /// Constructor with exception message string.
    explicit error_loading_file(const std::string& message) : std::runtime_error(message) {}
};


/// Exception class which is thrown if and openGL error occurred
class opengl_error : public std::runtime_error {
public:
    /// Constructor with exception message string.
    explicit opengl_error(const std::string& message) : std::runtime_error(message) {}
};

}
