cmake_minimum_required(VERSION 3.24)
project(MultiMap)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultiMap App.cpp ExtendedTest.h ExtendedTest.cpp ShortTest.h ShortTest.cpp MultiMapIterator.h MultiMapIterator.cpp MultiMap.h MultiMap.cpp)
