cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

project(stlLoad)

set(CMAKE_BUILD_TYPE Debug)


find_package(PkgConfig REQUIRED)
pkg_check_modules(SMPL REQUIRED smpl)
find_package(Eigen3 REQUIRED)
#find_package(smpl REQUIRED)


include_directories(${Boost_INCLUDE_DIRS}
                    ${SMPL_INCLUDE_DIRS} 
                    ${EIGEN3_INCLUDE_DIR}
                    )

link_directories(${SMPL_LIBRARY_DIRS})



add_executable(stlLoad stl_reader.h stl_load.cpp)

target_link_libraries(stlLoad ${SMPL_LIBRARIES} )
