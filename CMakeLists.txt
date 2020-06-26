cmake_minimum_required(VERSION 3.11)

project(bomberman)
file (GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/Sources/Main.cpp"
	"${PROJECT_SOURCE_DIR}/Sources/Player.cpp"
	"${PROJECT_SOURCE_DIR}/Sources/Map.cpp"
	"${PROJECT_SOURCE_DIR}/Sources/Bomb.cpp"
	"${PROJECT_SOURCE_DIR}/Sources/PowerUp.cpp"
	"${PROJECT_SOURCE_DIR}/Sources/IA.cpp"
	"${PROJECT_SOURCE_DIR}/Sources/Game.cpp")
add_executable(bomberman ${SOURCES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Dependencies/Irrlicht")
include("${PROJECT_SOURCE_DIR}/Dependencies/Irrlicht/FindIrrlicht.cmake")

IF (Irrlicht_FOUND)
    target_include_directories(bomberman PUBLIC "${Irrlicht_INCLUDE_DIRS}")
    target_include_directories(bomberman PUBLIC "Headers")
    target_link_libraries(bomberman PUBLIC "${Irrlicht_LIBRARIES}")
ELSE (Irrlicht_FOUND)
    MESSAGE(FATAL_ERROR "Irrlicht not found.")
ENDIF (Irrlicht_FOUND)

IF (WIN32 OR WIN64)
    add_custom_command(TARGET bomberman
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "${PROJECT_SOURCE_DIR}/Dependencies/Irrlicht/Irrlicht.dll" "${PROJECT_SOURCE_DIR}/build/Debug" )
    add_custom_command(TARGET bomberman
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        "PROJECT_SOURCE_DIR}/build/graphs" )
    add_custom_command(TARGET bomberman
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        "${PROJECT_SOURCE_DIR}/graphs" "${PROJECT_SOURCE_DIR}/build/graphs" )
ENDIF(WIN32 OR WIN64)

