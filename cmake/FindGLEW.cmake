#
# Try to find GLEW library and include path.
#
# GLEW_FOUND - System found GLEW
# GLEW_INCLUDE_PATH - include directory of GLEW
# GLEW_LIBRARY - GLEW library
# 

if (WIN32)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		$ENV{PROGRAMFILES}/GLEW/include
		$ENV{GLEW_DIR}/include)
	FIND_LIBRARY( GLEW_LIBRARY
		NAMES glew GLEW glew32 glew32s
		PATHS
		$ENV{PROGRAMFILES}/GLEW/lib
		$ENV{GLEW_DIR}/lib)
else (WIN32)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		/usr/include
		/usr/local/include
		/opt/local/include
		$ENV{GLEW_DIR}/include)
	FIND_LIBRARY( GLEW_LIBRARY
		NAMES GLEW glew
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		$ENV{GLEW_DIR}/lib)
endif (WIN32)

# check if anything was found
if (GLEW_INCLUDE_PATH)
	SET( GLEW_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
else (GLEW_INCLUDE_PATH)
	SET( GLEW_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
endif (GLEW_INCLUDE_PATH)

mark_as_advanced( GLEW_FOUND )

