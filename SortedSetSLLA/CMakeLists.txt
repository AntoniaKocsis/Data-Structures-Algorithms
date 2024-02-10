cmake_minimum_required(VERSION 3.24)
project(SortedSetSLLA)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortedSetSLLA main.cpp SortedSet.cpp SortedSet.h ExtendedTest.h ExtendedTest.cpp ShortTest.cpp ShortTest.h)
