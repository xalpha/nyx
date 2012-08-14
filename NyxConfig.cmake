##############################################################################
#                                                                            #
# This file is part of nyx, a lightweight C++ template library for OpenGL    #
#                                                                            #
# Copyright (C) 2012 Alexandru Duliu                                         #
#                                                                            #
# nxy is free software; you can redistribute it and/or                       #
# modify it under the terms of the GNU Lesser General Public                 #
# License as published by the Free Software Foundation; either               #
# version 3 of the License, or (at your option) any later version.           #
#                                                                            #
# nxy is distributed in the hope that it will be useful, but WITHOUT ANY     #
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS  #
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the #
# GNU General Public License for more details.                               #
#                                                                            #
# You should have received a copy of the GNU Lesser General Public           #
# License along with nxy. If not, see <http://www.gnu.org/licenses/>.        #
#                                                                            #
##############################################################################

# Config file for the nyx library
# It defines the following variables
#
# Nyx_INCLUDE_DIR - include directory for nyx headers
# Nyx_INCLUDE_DIRS - all include directories nyx needs
# Nyx_Nyx_LINK_LIBRARIES - all include directories nyx needs
# Nyx_LINK_LIBRARIES - all the libraries nyx needs

# set path
set( Nyx_DIR ${CMAKE_CURRENT_LIST_DIR})
set( ENV{Nyx_DIR} ${Nyx_DIR} )

# add module paths
list( APPEND CMAKE_MODULE_PATH ${Nyx_DIR}/cmake ${CMAKE_INSTALL_PREFIX}/share )

# find GLEW
find_package( GLEW )

# set the include dir
set( Nyx_INCLUDE_DIR "${Nyx_DIR}/include")

# set target names
set( Nyx_TARGET nyx )

# set compile definitions
set( Nyx_COMPILE_DEFINITIONS NYX CACHE INTERNAL "all compile definitions nyx needs"  )

# set linker flags
if( WIN32 )
    list( APPEND Nyx_LINK_FLAGS " /MANIFEST:NO" )
endif()

# set include directories
set( Nyx_INCLUDE_DIRS
    ${Nyx_INCLUDE_DIR}
    ${Nyx_INCLUDE_DIRS}
    ${GLEW_INCLUDE_PATH} CACHE INTERNAL "all include directories nyx needs" )

# link libraries
set( Nyx_LINK_LIBRARIES ${GLEW_LIBRARY} CACHE INTERNAL "all libs nyx needs" )

# enable C++11 support
#if( NOT WIN32 )
#    if( CMAKE_COMPILER_IS_GNUCXX )
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
#    else( CMAKE_COMPILER_IS_GNUCXX )
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Qunused-arguments")
#    endif()
#endif()



