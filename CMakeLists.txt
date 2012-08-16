##############################################################################
#                                                                            #
# This file is part of nyx, a lightweight C++ template library for OpenGL    #
#                                                                            #
# Copyright (C) 2012 Alexandru Duliu                                         #
#                                                                            #
# nyx is free software; you can redistribute it and/or                       #
# modify it under the terms of the GNU Lesser General Public                 #
# License as published by the Free Software Foundation; either               #
# version 3 of the License, or (at your option) any later version.           #
#                                                                            #
# nyx is distributed in the hope that it will be useful, but WITHOUT ANY     #
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS  #
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the #
# GNU General Public License for more details.                               #
#                                                                            #
# You should have received a copy of the GNU Lesser General Public           #
# License along with nyx. If not, see <http://www.gnu.org/licenses/>.        #
#                                                                            #
##############################################################################

cmake_minimum_required(VERSION 2.8)
project(Nyx)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# configure the project
include( NyxConfig.cmake )

# add the include files
list( APPEND Nyx_INC
    include/nyx/array_buffer.hpp
    include/nyx/buffer.hpp
    include/nyx/color_array_buffer.hpp
    include/nyx/element_buffer.hpp
    include/nyx/exception.hpp
    include/nyx/frame_buffer_object.hpp
    include/nyx/gl.hpp
    include/nyx/normal_array_buffer.hpp
    include/nyx/program.hpp
    include/nyx/shader.hpp
    include/nyx/texcoord_array_buffer.hpp
    include/nyx/texture.hpp
    include/nyx/util.hpp
    include/nyx/vertex_array_buffer.hpp
    include/nyx/vertex_buffer_object.hpp )

# set include directories
include_directories( ${Nyx_INCLUDE_DIRS} )

# add the target
add_custom_target( ${Nyx_TARGET} SOURCES ${Nyx_INC} )

# install
install(FILES ${Nyx_INC} DESTINATION "include/nyx" )
install(FILES "${CMAKE_CURRENT_LIST_DIR}/cmake/FindNyx.cmake" DESTINATION share )
