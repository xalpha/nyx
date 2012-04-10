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

#include <vector>
#include <GL/glew.h>


namespace nyx
{

/*
 * util.h
 *
 *  Created on: May 4, 2010
 *      Author: alex
 */

namespace util
{


template <typename T>
class type
{
        type(){}
        ~type(){}

public:
	// openGL types
	static inline unsigned int getGL();
        static inline bool isGL( unsigned int t );
	static inline bool isGLCompatible();

	// type checks
	static inline bool isSigned();
	static inline bool isInteger();

	static inline bool isUnsigned();
	static inline bool isFloatingPoint();
};


template<> inline unsigned int type<float>::getGL(){ return GL_FLOAT; }
template<> inline unsigned int type<double>::getGL(){ return GL_DOUBLE; }
template<> inline unsigned int type<int>::getGL(){ return GL_INT; }
template<> inline unsigned int type<short>::getGL(){ return GL_SHORT; }
template<> inline unsigned int type<char>::getGL(){ return GL_BYTE; }
template<> inline unsigned int type<unsigned int>::getGL(){ return GL_UNSIGNED_INT; }
template<> inline unsigned int type<unsigned short>::getGL(){ return GL_UNSIGNED_SHORT; }
template<> inline unsigned int type<unsigned char>::getGL(){ return GL_UNSIGNED_BYTE; }


template<typename T>
inline bool type<T>::isGL( const unsigned int t )
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
inline bool type<T>::isGLCompatible()
{
        return type<T>::isGL( type<T>::getGL() );
}


template<> inline bool type<float>::isSigned(){ return true; }
template<> inline bool type<double>::isSigned(){ return true; }
template<> inline bool type<int>::isSigned(){ return true; }
template<> inline bool type<short>::isSigned(){ return true; }
template<> inline bool type<char>::isSigned(){ return true; }
template<> inline bool type<unsigned int>::isSigned(){ return false; }
template<> inline bool type<unsigned short>::isSigned(){ return false; }
template<> inline bool type<unsigned char>::isSigned(){ return false; }


template<> inline bool type<float>::isInteger(){ return false; }
template<> inline bool type<double>::isInteger(){ return false; }
template<> inline bool type<int>::isInteger(){ return true; }
template<> inline bool type<short>::isInteger(){ return true; }
template<> inline bool type<char>::isInteger(){ return true; }
template<> inline bool type<unsigned int>::isInteger(){ return true; }
template<> inline bool type<unsigned short>::isInteger(){ return true; }
template<> inline bool type<unsigned char>::isInteger(){ return true; }


template<typename T>
inline bool type<T>::isUnsigned()
{
        return !type<T>::isSigned();
}


template<typename T>
inline bool type<T>::isFloatingPoint()
{
        return !type<T>::isInteger();
}


template<typename Tsrc, typename Tdst>
inline void convert( const std::vector<Tsrc> &source, std::vector<Tdst> &destination )
{
	destination.resize(source.size());

	for( size_t i=0; i<destination.size(); i++ )
		destination[i] = (Tdst) source[i];
}


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
