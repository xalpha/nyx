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

#  Try to find Nyx
#
#  Nyx_FOUND - System has Nyx
#  Nyx_INCLUDE_DIRS - The Nyx include directories
#  Nyx_LIBRARIES - All libraries Nyx needs


# try to find the include dir
find_path( Nyx_INCLUDE_DIR 
    NAMES
        nyx/CameraCalibration.hpp
        nyx/Finder.hpp
    PATHS
	    $ENV{Nyx_DIR}/include
	    %{CMAKE_INSTALL_PREFIX}/include
        /usr/include
        /usr/local/include
        /opt/include
        /opt/local/install
    PATH_SUFFIXES
        nyx )

# check if this is a valid component
if( TARGET ${Nyx_INCLUDE_DIR} )
    # include the component
    MESSAGE( STATUS "Nyx found.")
else()
    MESSAGE( FATAL_ERROR "Nyx target not available.")
endif()

# set the include dirs
set( Nyx_INCLUDE_DIRS 
    ${Nyx_INCLUDE_DIR}
    ${Nyx_INCLUDE_DIR}/nyx )
    
    
#####
## Dependencies
###

# find GLEW
if( NOT GLEW_FOUND )
    find_package( GLEW REQUIRED )
endif()
list( APPEND Nyx_INCLUDE_DIRS ${GLEW_INCLUDE_PATH} )
list( APPEND Nyx_LIBRARIES ${GLEW_LIBRARY} )

