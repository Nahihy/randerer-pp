cmake_minimum_required(VERSION 3.14)

project(randererppshowcase)

find_package(OpenGL REQUIRED)

add_executable(randererppshowcase main.cpp)

set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders" CACHE STRING "Shader directory")
set(TEXTURE_DIR "${CMAKE_SOURCE_DIR}/textures" CACHE STRING "Texture directory")

add_subdirectory(randerer++)

target_link_libraries(randererppshowcase PRIVATE randerer++ OpenGL::GL glfw glad stb)
