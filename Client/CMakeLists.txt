cmake_minimum_required(VERSION 3.3)
project(Client)

# Gather c++ files
file(GLOB_RECURSE SRC_FILES 
	../Source/*.h
	../Source/*.cpp
	Source/*.cpp
	Source/*.h
)

set(SharedSourceDir ${CMAKE_SOURCE_DIR}/Source)

file(GLOB_RECURSE SRC_OBJECT
    "${SharedSourceDir}/Core/Object/*.cpp"
    "${SharedSourceDir}/Core/Object/*.h"
)
file(GLOB_RECURSE SRC_DEBUG
    "${SharedSourceDir}/Core/Debug/*.cpp"
    "${SharedSourceDir}/Core/Debug/*.h"
)
file(GLOB_RECURSE SRC_ACTOR
    "${SharedSourceDir}/Core/Actor/*.cpp"
    "${SharedSourceDir}/Core/Actor/*.h"
)
file(GLOB_RECURSE SRC_WORLD
    "${SharedSourceDir}/Core/World/*.cpp"
    "${SharedSourceDir}/Core/World/*.h"
)
file(GLOB_RECURSE SRC_ENGINE
    "${SharedSourceDir}/Core/Engine/*.cpp"
    "${SharedSourceDir}/Core/Engine/*.h"
)
file(GLOB_RECURSE SRC_COMPONENT
    "${SharedSourceDir}/Core/Component/*.cpp"
    "${SharedSourceDir}/Core/Component/*.h"
)

source_group("Core\\Object" FILES ${SRC_OBJECT})
source_group("Core\\Debug" FILES ${SRC_DEBUG})
source_group("Core\\Actor" FILES ${SRC_ACTOR})
source_group("Core\\World" FILES ${SRC_WORLD})
source_group("Core\\Engine" FILES ${SRC_ENGINE})
source_group("Core\\Component" FILES ${SRC_COMPONENT})

FILE(GLOB_RECURSE children RELATIVE ${SharedSourceDir} ${SharedSourceDir}/*)
FOREACH(child ${children})

IF(IS_DIRECTORY ${SharedSourceDir}/${curdir}/${child})
	message( ${curdir}/${child})
	include_directories ( ${curdir}/${child})
ENDIF()
ENDFOREACH()

include_directories ("../Dependencies/Include/Ogre")
include_directories ("../Dependencies/Include/Boost")
include_directories ("../Source")
include_directories ("Source")

LINK_DIRECTORIES(Client ${LIB_DIR}) #must come before add_executable

add_executable(Client ${SRC_FILES})

message("${LIB_DIR}}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	
	TARGET_LINK_LIBRARIES(Client ${LIB_DIR}/OgreMain_d.lib)
	TARGET_LINK_LIBRARIES(Client ${LIB_DIR}/OIS_d.lib)
	#TARGET_LINK_LIBRARIES(Client ${LIB_DIR}/sfml-window-d.lib)#TEMP
	#TARGET_LINK_LIBRARIES(Client ${LIB_DIR}/sfml-graphics-d.lib)#TEMP
	#TARGET_LINK_LIBRARIES(Client ${LIB_DIR}/sfml-system-d.lib)#TEMP
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

	if (${CMAKE_GENERATOR} MATCHES "Visual Studio 14")
		 set (DLL_TO_DBG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
		 set (DLL_TO_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
	else()
		 set (DLL_TO_DBG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
		 set (DLL_TO_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	endif()

	file(MAKE_DIRECTORY ${DLL_TO_DBG})
	file(GLOB_RECURSE nativeLibs ../Dependencies/bin/Windows/x86/Debug/*.dll)
	foreach(AddonFile ${nativeLibs})
		get_filename_component(OUT_DIR ${AddonFile} DIRECTORY)
		string(REGEX REPLACE "${CMAKE_CURRENT_LIST_DIR}/../Dependencies/bin/Windows/x86/Debug"
				"" OUT_DIR ${OUT_DIR})
	
		
		add_custom_command(TARGET GET Client PRE_BUILD
				COMMAND ${CMAKE_COMMAND} -E
				copy ${AddonFile} ${DLL_TO_DBG}/)
			message(${DLL_TO_DBG})
	endforeach(AddonFile)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

