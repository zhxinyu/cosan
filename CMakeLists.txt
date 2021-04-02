cmake_minimum_required(VERSION 3.17)
project (cosan)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include_directories(/usr/local/include/ /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan)
add_subdirectory ("cosan")
add_subdirectory ("docs")

set(CMAKE_CXX_STANDARD 20)