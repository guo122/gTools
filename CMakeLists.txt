cmake_minimum_required (VERSION 3.0.2)

project(gTools)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)

set(CMAKE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_ROOT_DIR}/BuildScript/cmake/Config.cmake)
include(${CMAKE_ROOT_DIR}/BuildScript/cmake/Macros.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

add_subdirectory("src")
