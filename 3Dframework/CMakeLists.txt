cmake_minimum_required(VERSION 3.14)

project(3Dframework)

# add_library(3Dframework)
target_link_libraries(3Dframework PUBLIC assimp)
target_include_directories(3Dframework include)
