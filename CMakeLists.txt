# CMakeList.txt : CMake project for MusicVisualizer, include source and define
# project specific logic here.

cmake_minimum_required(VERSION 3.8)
project(MusicVisualizer)

# Build for platform
if (WIN32)
	if (NOT DEFINED ${VAR_NAME})
		set(SDL2_PATH "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2")
	endif (NOT DEFINED ${VAR_NAME})
	set(SDL2_INCLUDE_DIRS "${SDL2_PATH}/include")

	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_LIB_DIR "${SDL2_PATH}/lib/x64")
	else ()
		set(SDL2_LIB_DIR "${SDL2_PATH}/lib/x86")
	endif ()

	file(COPY "${CMAKE_SOURCE_DIR}/build/test.wav" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY "${SDL2_LIB_DIR}/SDL2.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	link_directories(${SDL2_LIB_DIR})
else ()
	set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -pthread")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})
endif ()

add_executable(
	${PROJECT_NAME}

	# Include headers
	"src/Logger.h"
	"src/Exception/AppException.h"
	"src/Graphic/Window.h"
	"src/Graphic/Renderer.h"
	"src/Graphic/SDL/RendererWrapper.h"
	"src/Graphic/SDL/Visualizer.h"
	"src/Audio/Player.h"
	"src/Audio/AudioData.h"
	"src/Audio/SDL/AudioWrapper.h"

	# Include impl
	"src/main.cpp"
	"src/Logger.cpp"
	"src/Graphic/Renderer.cpp"
	"src/Graphic/SDL/RendererWrapper.cpp"
	"src/Graphic/SDL/Visualizer.cpp"
	"src/Audio/Player.cpp"
	"src/Audio/SDL/AudioWrapper.cpp"
)

include_directories(${SDL2_INCLUDE_DIRS} src)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
else ()
	string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif ()
