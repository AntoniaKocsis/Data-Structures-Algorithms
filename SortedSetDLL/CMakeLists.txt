cmake_minimum_required(VERSION 3.24)
project(SortedSetDLL)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortedSetDLL main.cpp ShortTest.cpp ShortTest.h SortedSet.cpp SortedSet.h ExtendedTest.h ExtendedTest.cpp)
