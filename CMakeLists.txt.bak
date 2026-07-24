cmake_minimum_required(VERSION 3.14)
project(test)

add_executable(test main.cpp mesh.hpp)

find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

add_subdirectory(randerer++)
# add_subdirectory(assimp)

target_link_libraries(test PRIVATE randerer++ OpenGL::GL glad stb glfw glm assimp)

