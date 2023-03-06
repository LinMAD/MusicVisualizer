# CMakeList.txt : CMake project for MusicVisualizer, include source and define
# project specific logic here.

cmake_minimum_required(VERSION 3.8)

project(MusicVisualizer)
#
#if (COMMAND cmake_policy)
#    cmake_policy(SET CMP0003 NEW)
#endif (COMMAND cmake_policy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

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

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(FFTW3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE FFTW3::fftw3)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
