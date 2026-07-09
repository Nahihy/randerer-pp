cmake_minimum_required(VERSION 3.14)
project(randerer++)

if(NOT DEFINED SHADER_DIR)
  set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders" CACHE STRING "Shader directory")
endif()

if(NOT DEFINED TEXTURE_DIR)
  set(TEXTURE_DIR "${CMAKE_SOURCE_DIR}/textures" CACHE STRING "Texture directory")
endif()

add_library(randerer++ 
  src/bufferSet.hpp
  src/shader.hpp
  src/texture.hpp
  src/sprite.hpp
  src/window.hpp
)

find_package(OpenGL REQUIRED)

add_subdirectory(baseLibs/glad)
add_subdirectory(baseLibs/glfw)
add_subdirectory(baseLibs/stb)
add_subdirectory(baseLibs/glm)

target_include_directories(randerer++ PUBLIC include)

target_link_libraries(randerer++ PUBLIC OpenGL::GL glad stb glfw glm)

add_custom_target(copy-shaders-dir ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} ${CMAKE_BINARY_DIR}/shaders
)
add_custom_target(copy-texture-dir ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${TEXTURE_DIR} ${CMAKE_BINARY_DIR}/textures
)
