cmake_minimum_required(VERSION 2.8)

project(soc)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(modules)
add_subdirectory(apps)

