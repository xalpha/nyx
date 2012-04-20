cmake_minimum_required(VERSION 2.8)
project(Nyx)

# set paths
set( NYX_ROOT_DIR ${CMAKE_SOURCE_DIR} )
set( NYX_INCLUDES ${NYX_ROOT_DIR} )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${NYX_ROOT_DIR}")
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${NYX_ROOT_DIR}/cmake")

# find libraries
find_package( GLEW )
find_package( GLUT )

# check if the libraries were found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_INCLUDE_PATH )
find_package_handle_standard_args(GLUT DEFAULT_MSG GLUT_INCLUDE_DIR )

