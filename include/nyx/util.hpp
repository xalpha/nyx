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

#include <vector>
#include <limits>

#define GLEW_STATIC
#include <GL/glew.h>

#include <nyx/exception.hpp>


namespace nyx
{

/*
 * util.hpp
 *
 *  Created on: May 4, 2010
 *      Author: alex
 */

namespace util
{


/////
// Type
///

template <typename T>
class type
{
    type(){}
    ~type(){}

public:
    // openGL types
    static inline unsigned int GL();
    static inline bool is_GL( unsigned int t );
    static inline bool is_GL_compatible();

    // type checks
    static inline bool is_signed();
    static inline bool is_integer();

    // type independent values
    static inline T zero();
    static inline T one();
};


template<> inline unsigned int type<float>::GL(){ return GL_FLOAT; }
template<> inline unsigned int type<double>::GL(){ return GL_DOUBLE; }
template<> inline unsigned int type<int>::GL(){ return GL_INT; }
template<> inline unsigned int type<short>::GL(){ return GL_SHORT; }
template<> inline unsigned int type<char>::GL(){ return GL_BYTE; }
template<> inline unsigned int type<unsigned int>::GL(){ return GL_UNSIGNED_INT; }
template<> inline unsigned int type<unsigned short>::GL(){ return GL_UNSIGNED_SHORT; }
template<> inline unsigned int type<unsigned char>::GL(){ return GL_UNSIGNED_BYTE; }


template<typename T>
inline bool type<T>::is_GL( const unsigned int t )
{
    switch( t )
    {
        case GL_FLOAT : return true;
        case GL_DOUBLE :  return true;
        case GL_INT :  return true;
        case GL_SHORT :  return true;
        case GL_BYTE :  return true;
        case GL_UNSIGNED_INT :  return true;
        case GL_UNSIGNED_SHORT :  return true;
        case GL_UNSIGNED_BYTE :  return true;
        default : return false;
    }
}


template<typename T>
inline bool type<T>::is_GL_compatible()
{
    return type<T>::is_GL( type<T>::GL() );
}


template<typename T>
inline bool type<T>::is_signed()
{
    return std::numeric_limits<T>::is_signed;
}


template<typename T>
inline bool type<T>::is_integer()
{
    return std::numeric_limits<T>::is_integer;
}


template<typename T>
inline T type<T>::zero()
{
    return static_cast<T>(0);
}


template<typename T>
inline T type<T>::one()
{
    if( is_integer() )
        return std::numeric_limits<T>::max();
    else
        return static_cast<T>(1);
}



/////
// Convert between vector of different base types
///

template<typename Tsrc, typename Tdst>
inline void convert( const std::vector<Tsrc> &source, std::vector<Tdst> &destination )
{
	destination.resize(source.size());

	for( size_t i=0; i<destination.size(); i++ )
		destination[i] = (Tdst) source[i];
}




/////
// Channels
///

// helper for setting channels
#define NYX_FORMAT_CHANNELS( f,c ) case f : return c;
#define NYX_FORMAT_CHANNELS_ALL( f,c ) NYX_FORMAT_CHANNELS( f, c ) \
                                       NYX_FORMAT_CHANNELS( f ## 4, c ) \
                                       NYX_FORMAT_CHANNELS( f ## 8, c ) \
                                       NYX_FORMAT_CHANNELS( f ## 12, c ) \
                                       NYX_FORMAT_CHANNELS( f ## 16, c ) \

template<typename F>
inline size_t channels( F format )
{
    switch( format )
    {
        // set 1 channel
        NYX_FORMAT_CHANNELS( GL_COLOR_INDEX,    1 )
        NYX_FORMAT_CHANNELS( GL_RED,            1 )
        NYX_FORMAT_CHANNELS( GL_GREEN,          1 )
        NYX_FORMAT_CHANNELS( GL_BLUE,           1 )
        NYX_FORMAT_CHANNELS_ALL( GL_ALPHA,      1 )
        NYX_FORMAT_CHANNELS_ALL( GL_INTENSITY,  1 )
        NYX_FORMAT_CHANNELS_ALL( GL_LUMINANCE,  1 )
        NYX_FORMAT_CHANNELS( GL_DEPTH_COMPONENT,1 )

        // set 2 channels
        NYX_FORMAT_CHANNELS( GL_LUMINANCE_ALPHA,    2 )
        NYX_FORMAT_CHANNELS( GL_LUMINANCE4_ALPHA4,  2 )
        NYX_FORMAT_CHANNELS( GL_LUMINANCE8_ALPHA8,  2 )
        NYX_FORMAT_CHANNELS( GL_LUMINANCE12_ALPHA12,2 )
        NYX_FORMAT_CHANNELS( GL_LUMINANCE16_ALPHA16,2 )

        // set 3 channels
        NYX_FORMAT_CHANNELS_ALL( GL_RGB,    3 )
        NYX_FORMAT_CHANNELS( GL_BGR,    3 )

        // set 4 channels
        NYX_FORMAT_CHANNELS_ALL( GL_RGBA,   4 )
        NYX_FORMAT_CHANNELS( GL_BGRA,   4 )

        // default
        default:
            throw nyx::invalid_parameter( "nyx::util::format: unknown pixel format." );
    }
}

// undefine macros
#undef NYX_FORMAT_CHANNELS_ALL
#undef NYX_FORMAT_CHANNELS


//class Context
//{
//public:
//	Context()
//{
//	bool Context::checkExtensionSupport( const char *str )
//	{
//		GLenum err = glewIsSupported(str);
//		return GLEW_OK == err;
//}
//	~Context();
//
//	static bool checkExtensionSupport( const char *str )
//{
	//	// adapter and driver information
	//	std::cout << "VENDOR = " << glGetString( GL_VENDOR ) << "\n";
	//	std::cout << "RENDERER = " << glGetString( GL_RENDERER ) << "\n";
	//	std::cout << "VERSION = " << glGetString( GL_VERSION ) << "\n";
	//
	//	// opengl version
	//	printExtensionSupport("GL_VERSION_1_1");
	//	printExtensionSupport("GL_VERSION_1_2");
	//	printExtensionSupport("GL_VERSION_1_3");
	//	printExtensionSupport("GL_VERSION_1_4");
	//	printExtensionSupport("GL_VERSION_1_5");
	//	printExtensionSupport("GL_VERSION_2_0");
	//	printExtensionSupport("GL_VERSION_2_1");
	//	printExtensionSupport("GL_VERSION_3_0");
	//	printExtensionSupport("GL_VERSION_3_1");
	//	printExtensionSupport("GL_VERSION_3_2");
//}
//	static void printExtensionSupport( const char *str )
//{
	//	std::cout << str;
	//	if(checkExtensionSupport(str))
	//		std::cout << " = OK\n";
	//	else
	//		std::cout << " = MISSING\n";
//}
//
//	static void checkGLVersion();
//};


}
}
