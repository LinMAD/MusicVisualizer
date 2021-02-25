# CMakeList.txt : CMake project for MusicVisualizer, include source and define
# project specific logic here.

cmake_minimum_required(VERSION 3.8)

project(MusicVisualizer)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(VCPKG_ROOT $ENV{VCPKG_ROOT})
set(VCPKG_ROOT "E:/vcpkg")

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	file(TO_CMAKE_PATH "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CMAKE_TOOLCHAIN_FILE)
endif()

# Build for platform
if (WIN32)
	if(CMAKE_SIZEOF_VOID_P MATCHES 8)
		set(FFTW_ROOT "${VCPKG_ROOT}/packages/fftw3_x64-windows/share")
		set(SDL2_ROOT "${VCPKG_ROOT}/packages/sdl2_x64-windows/share")
	else()
		set(FFTW_ROOT "${VCPKG_ROOT}/packages/fftw3_x86-windows/share")
		set(SDL2_ROOT "${VCPKG_ROOT}/packages/sdl2_x86-windows/share")
	endif()

	file(COPY "${CMAKE_SOURCE_DIR}/build/test.wav" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()

# Build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
	file(COPY "${SDL2_ROOT}/../debug/bin/SDL2d.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY "${FFTW_ROOT}/../bin/fftw3.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()

set(FFTW3_DIR ${FFTW_ROOT}/fftw3)
set(SDL2_DIR ${SDL2_ROOT}/sdl2)

find_package(SDL2 CONFIG REQUIRED)
find_package(FFTW3 CONFIG REQUIRED)

add_executable(
		${PROJECT_NAME} "src/main.cpp"
		"src/Exception/AppException.h"
		"src/Graphic/Window.h"
		"src/Audio/SDL/AudioData.h"

		"src/Logger.h" "src/Logger.cpp"
		"src/Graphic/Renderer.h" "src/Graphic/Renderer.cpp"
		"src/Graphic/SDL/RendererWrapper.h" "src/Graphic/SDL/RendererWrapper.cpp"
		"src/Graphic/SDL/Visualizer.h" "src/Graphic/SDL/Visualizer.cpp"
		"src/Audio/Player.h" "src/Audio/Player.cpp"
		"src/Audio/SDL/Calculation/AudioWrapper.h" "src/Audio/SDL/Calculation/AudioWrapper.cpp"
)

include_directories(${PROJECT_NAME} src)
include_directories(${SDL2_INCLUDE_DIRS} src)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

target_include_directories(${PROJECT_NAME} PUBLIC ${FFTW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE FFTW3::fftw3)
