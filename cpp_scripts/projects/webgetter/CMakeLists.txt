cmake_minimum_required(VERSION 3.4)
project(webgetter)

# compile config
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# add_compile_options(-std=c++11)

# lib/exe config
# find_package(cpr REQUIRED)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git)
FetchContent_MakeAvailable(cpr)

add_executable(webgetter src/multiThread.cpp)
target_link_libraries(webgetter cpr::cpr)

