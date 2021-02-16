# CMakeList.txt : CMake project for MusicVisualizer, include source and define
# project specific logic here.

cmake_minimum_required(VERSION 3.8)
project(MusicVisualizer)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

if (WIN32)
	set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/include")

	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_LIB_DIR  "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x64")
		file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL2/lib/x64/SDL2.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	else ()
		set(SDL2_LIB_DIR  "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x86")
		file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL2/lib/x86/SDL2.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	endif ()

	link_directories(${SDL2_LIB_DIR})
else ()
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

	find_package(SDL2 REQUIRED)
	string(STRIP "${SDL2_LIBRARIES}" src)
	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif ()

include_directories(${SDL2_INCLUDE_DIRS} src)

file(GLOB SOURCES
	# Include headers
	"src/*.h"
	"src/Exception/*.h"
	"src/Graphic/*.h"
    "src/Graphic/SDL/*.h"
	# Include impl
	"src/*.cpp"
	"src/Exception/*.cpp"
	"src/Graphic/*.cpp"
    "src/Graphic/SDL/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
