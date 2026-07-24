cmake_minimum_required(VERSION 3.14)

project(randererppshowcase)

find_package(OpenGL REQUIRED)

add_executable(randererppshowcase main.cpp)

add_subdirectory(randerer++)

target_link_libraries(randererppshowcase PRIVATE randerer++ OpenGL::GL glfw glad stb)
