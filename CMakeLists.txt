cmake_minimum_required(VERSION 3.14)
project(bms-monitor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
set(CMAKE_CXX_FLAGS_RELEASE "/MT")

add_subdirectory(monitor)
add_subdirectory(external/googletest)
add_subdirectory(external/rapidcheck)
add_subdirectory(external/yaml-cpp)
add_subdirectory(external/CLI11)
