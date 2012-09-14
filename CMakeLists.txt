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

cmake_minimum_required(VERSION 2.8)
project(Nyx)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# set some variabiles
set( CMAKE_BUILD_TYPE Debug )
if( NOT WIN32 )
    set( BUILD_SHARED_LIBS TRUE )
endif()

# configure the project
include( NyxConfig.cmake )

# add the include files
list( APPEND Nyx_INC
    include/nyx/array_buffer.hpp
    include/nyx/buffer.hpp
    include/nyx/context.hpp
    include/nyx/color_array_buffer.hpp
    include/nyx/element_buffer.hpp
    include/nyx/exception.hpp
    include/nyx/frame_buffer_object.hpp
    include/nyx/normal_array_buffer.hpp
    include/nyx/program.hpp
    include/nyx/shader.hpp
    include/nyx/test.hpp
    include/nyx/texcoord_array_buffer.hpp
    include/nyx/texture.hpp
    include/nyx/util.hpp
    include/nyx/vertex_array_buffer.hpp
    include/nyx/vertex_buffer_object.hpp )

# set include directories
include_directories( ${Nyx_INCLUDE_DIRS} )

# add the target
add_custom_target( ${Nyx_TARGET} SOURCES ${Nyx_INC} )

# configure target
set_target_properties(${Nyx_TARGET}
    PROPERTIES
        PUBLIC_HEADER "${Nyx_INC}"
        COMPILE_DEFINITIONS "${Nyx_COMPILE_DEFINITIONS}"
        COMPILE_FLAGS "${Nyx_COMPILE_FLAGS}"
        LINK_FLAGS "${Nyx_LINK_FLAGS}" )

# install module finder
install(FILES "${CMAKE_CURRENT_LIST_DIR}/cmake/FindNyx.cmake" DESTINATION share )

install(FILES ${Nyx_INC} DESTINATION "include/nyx" )


# enable testing
ENABLE_TESTING()

# add tests
add_subdirectory(test)
