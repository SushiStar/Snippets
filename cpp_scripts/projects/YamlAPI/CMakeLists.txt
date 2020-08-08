cmake_minimum_required(VERSION 3.4)
project(yaml_api_apply)

# compile config
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-std=c++11)

# lib/exe config
find_package(yaml-cpp REQUIRED)
include_directories(yaml-cpp/include)

add_executable(yamlimp src/main.cpp)
target_link_libraries(yamlimp yaml-cpp)

