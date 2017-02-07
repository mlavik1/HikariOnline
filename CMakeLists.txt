cmake_minimum_required(VERSION 3.3)
project(Hikari)

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-malign-double)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "USE_C99_MATH;_DEBUG")

set(BUILD_ROOT "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

SET(LIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies/lib/Windows/x86/Debug")

# compiler
if(${CMAKE_COMPILER_IS_GNUCC})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")
else("")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(${CMAKE_COMPILER_IS_GNUCC})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# linker flags
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(OPENGL_LINK "")
	SET(GCC_LINK_FLAGS    "-framework OpenGL -v")
	SET( CMAKE_EXE_LINKER_FLAGS  "${GCC_LINK_FLAGS}" )
	#  -framework GLUT
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	SET(OPENGL_LINK "OpenGL32")
ELSE("")
	SET(OPENGL_LINK "GL")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# project
add_subdirectory(Client)

