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

# find glut
find_package( GLUT QUIET )

# if GLUT found
if( GLUT_FOUND )

    # set include directories
    include_directories( ${Nyx_INCLUDE_DIRS} )

#    # add test for context
#    set( Nyx_Test_context test_context )
#    add_executable( ${Nyx_Test_context} test_context.cpp )
#    target_link_libraries( ${Nyx_Test_context} -lm -lc -Wall ${Nyx_LINK_LIBRARIES} ${GLUT_LIBRARIES} )
#    add_test( ${Nyx_Test_context} ${Nyx_Test_context} )

    # add test for buffer
    set( Nyx_Test_buffer test_buffer )
    add_executable( ${Nyx_Test_buffer} test_buffer.cpp )
    target_link_libraries( ${Nyx_Test_buffer} -lm -lc -Wall ${Nyx_LINK_LIBRARIES} ${GLUT_LIBRARIES} )
    add_test( ${Nyx_Test_buffer} ${Nyx_Test_buffer} )

elseif()
    message( WARNING "GLUT not found, tests disabled." )
endif()
