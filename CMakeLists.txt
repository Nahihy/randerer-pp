cmake_minimum_required(VERSION 3.14)
project(test)

add_executable(test main.cpp)

find_package(OpenGL REQUIRED)

add_subdirectory(randerer++)

target_link_libraries(test PRIVATE randerer++ OpenGL::GL glad stb glfw glm)

