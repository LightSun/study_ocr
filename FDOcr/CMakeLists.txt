cmake_minimum_required(VERSION 3.10)

project(FDOcr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
##
include(cmake/ENV.cmake)

include_directories(./)
SET(PY_BIND11_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/pybind11)

#fd
find_package(FastDeploy)
include_directories(${FastDeploy_INCLUDE_DIRS})
##
add_subdirectory(infer/)
add_subdirectory(third_party/pybind11)
add_subdirectory(pybind/)

