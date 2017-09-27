cmake_minimum_required(VERSION 3.3)
project(GameServer)

add_definitions(-DHIKARI_GAMESERVER)

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
file(GLOB_RECURSE SRC_ENGINE
    "${SharedSourceDir}/Core/Engine/*.cpp"
    "${SharedSourceDir}/Core/Engine/*.h"
)
file(GLOB_RECURSE SRC_DEBUG
    "${SharedSourceDir}/Core/Debug/*.cpp"
    "${SharedSourceDir}/Core/Debug/*.h"
)
file(GLOB_RECURSE SRC_NETWORKING
    "${SharedSourceDir}/Core/Networking/*.cpp"
    "${SharedSourceDir}/Core/Networking/*.h"
)
file(GLOB_RECURSE SRC_CONTROLLER
    "${SharedSourceDir}/Core/Controller/*.cpp"
    "${SharedSourceDir}/Core/Controller/*.h"
)
file(GLOB_RECURSE SRC_SERIALISATION
    "${SharedSourceDir}/Core/Serialisation/*.cpp"
    "${SharedSourceDir}/Core/Serialisation/*.h"
)
file(GLOB_RECURSE SRC_GAMESERVER
    "Source/*.cpp"
    "Source/*.h"
)

source_group("Core\\Object" FILES ${SRC_OBJECT})
source_group("Core\\Debug" FILES ${SRC_DEBUG})
source_group("Core\\Networking" FILES ${SRC_NETWORKING})
source_group("Core\\Controller" FILES ${SRC_CONTROLLER})
source_group("Core\\Engine" FILES ${SRC_ENGINE})
source_group("Core\\Serialisation" FILES ${SRC_SERIALISATION})
source_group("GameServer" FILES ${SRC_GAMESERVER})

include_directories ("../Dependencies/Include/SDL2")
include_directories ("../Dependencies/Include/Ogre")
include_directories ("../Dependencies/Include/Boost")
include_directories ("../Dependencies/Include/SFML-2.4.1")
include_directories ("../Dependencies/Include/MYGUI")
include_directories ("../Source")
include_directories ("Source")

LINK_DIRECTORIES(GameServer ${LIB_DIR}) #must come before add_executable

add_executable(GameServer ${SRC_FILES})

message("${LIB_DIR}}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/SDL2.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/SDL2main.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/SDL2_net.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/OgreMain_d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/OIS_d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/sfml-system-d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/sfml-main-d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/sfml-network-d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/EditorFramework_d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/MyGUI.OgrePlatform_d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/MyGUIEngine_d.lib)
	TARGET_LINK_LIBRARIES(GameServer ${LIB_DIR}/Plugin_StrangeButton_d.lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# ----- DLL ------------------------------------------------------------------
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
	
		
		add_custom_command(TARGET GET GameServer PRE_BUILD
				COMMAND ${CMAKE_COMMAND} -E
				copy ${AddonFile} ${DLL_TO_DBG}/)
	endforeach(AddonFile)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

