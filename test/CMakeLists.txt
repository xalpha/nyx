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

# set include directories
include_directories( ${Nyx_INCLUDE_DIRS} )

# add test for buffer
set( Nyx_Test_buffer test_assert )
add_executable( ${Nyx_Test_buffer} test_assert.cpp )
target_link_libraries( ${Nyx_Test_buffer} -lm -lc -Wall ${Nyx_LINK_LIBRARIES} )
add_test( ${Nyx_Test_buffer} ${Nyx_Test_buffer} )

# add test for buffer
set( Nyx_Test_buffer test_buffer )
add_executable( ${Nyx_Test_buffer} test_buffer.cpp )
target_link_libraries( ${Nyx_Test_buffer} -lm -lc -Wall ${Nyx_LINK_LIBRARIES} )
add_test( ${Nyx_Test_buffer} ${Nyx_Test_buffer} )

