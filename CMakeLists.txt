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
set(VCPKG_ROOT "E:/vcpkg") # TODO Fix it

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	file(TO_CMAKE_PATH "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CMAKE_TOOLCHAIN_FILE)
endif()

# Build for platform
if (WIN32)
	set(PLATFORM_ARCH "x86")

	if(CMAKE_SIZEOF_VOID_P MATCHES 8)
		set(PLATFORM_ARCH "x64")
	endif()

	set(FFTW_ROOT "${VCPKG_ROOT}/packages/fftw3_${PLATFORM_ARCH}-windows/share")
	set(SDL2_ROOT "${VCPKG_ROOT}/packages/sdl2_${PLATFORM_ARCH}-windows/share")
	set(imgui_ROOT "${VCPKG_ROOT}/packages/imgui_${PLATFORM_ARCH}-windows/share")
	set(GLEW_ROOT "${VCPKG_ROOT}/packages/glew_${PLATFORM_ARCH}-windows/share")


	file(COPY "${CMAKE_SOURCE_DIR}/build/test.wav" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()

# Build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
	file(COPY "${SDL2_ROOT}/../debug/bin/SDL2d.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY "${FFTW_ROOT}/../bin/fftw3.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY "${GLEW_ROOT}/../debug/bin/glew32d.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()

add_executable(
		${PROJECT_NAME} src/main.cpp
		src/Exception/AppException.h
		src/Graphic/Window.h
		src/Audio/SDL/AudioData.h

		src/Logger.h src/Logger.cpp
		src/Graphic/Renderer.h src/Graphic/Renderer.cpp
		src/Graphic/SDL/RendererWrapper.h src/Graphic/SDL/RendererWrapper.cpp
        src/Audio/Player.h src/Audio/Player.cpp
		src/Audio/SDL/Calculation/AudioWrapper.h src/Audio/SDL/Calculation/AudioWrapper.cpp
        src/Graphic/Gui/Screen.cpp src/Graphic/Gui/Screen.h
)
include_directories(${PROJECT_NAME} src)

set(SDL2_DIR ${SDL2_ROOT}/sdl2)
find_package(SDL2 CONFIG REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

set(FFTW3_DIR ${FFTW_ROOT}/fftw3)
find_package(FFTW3 CONFIG REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${FFTW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE FFTW3::fftw3)

set(GLEW_DIR ${GLEW_ROOT}/glew)
set(GLEW_LIBRARIES ${GLEW_ROOT}/../lib)
set(GLEW_INCLUDE_DIRS ${GLEW_ROOT}/../include)
find_package(GLEW REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

set(imgui_DIR ${imgui_ROOT}/imgui)
find_package(imgui CONFIG REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${imgui_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
