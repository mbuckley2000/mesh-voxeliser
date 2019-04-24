cmake_minimum_required(VERSION 3.13)
project(voxelise)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(lib/libigl/include)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(voxelise src/main.cpp tests/EigenTests.cpp tests/BoxTests.cpp src/Box.cpp include/Box.h include/Vectors.h src/Triangle.cpp include/Triangle.h include/Intersectable.h tests/TriangleTests.cpp src/Mesh.cpp include/Mesh.h tests/MeshTests.cpp)
target_link_libraries(voxelise gtest gtest_main)