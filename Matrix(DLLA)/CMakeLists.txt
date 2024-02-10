cmake_minimum_required(VERSION 3.24)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(Matrix App.cpp ExtendedTest.cpp Matrix.cpp ShortTest.cpp)
