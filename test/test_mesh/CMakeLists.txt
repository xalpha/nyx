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
project(test_mesh)

# turn stuff on
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

# find Qt5
find_package( Qt5Widgets REQUIRED )
find_package( Qt5OpenGL REQUIRED)

# set include paths
include_directories(
    include
    ui
    ${Nyx_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR} )

# set the header files of QObject derived classes
set( TEST_MESH_QT_HPP test_mesh.hpp )
set( TEST_MESH_INC test_mesh.hpp )
set( TEST_MESH_SRC test_mesh.cpp main.cpp )

# run the qt moc (meta object compiler)
QT5_WRAP_CPP( TEST_MESH_QT_HPP_MOC ${TEST_MESH_QT_HPP} )

# add the exec
add_executable( ${PROJECT_NAME} ${TEST_MESH_SRC} ${TEST_MESH_INC} ${TEST_MESH_QT_HPP_MOC} )
target_link_libraries( ${PROJECT_NAME} ${Nyx_LINK_LIBRARIES} )

# this is how to connect modules in qt5
qt5_use_modules( ${PROJECT_NAME} Widgets OpenGL )

#ADD_TEST( testd [Debug|Release] ${PROJECT_NAME} )
