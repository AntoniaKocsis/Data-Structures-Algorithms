cmake_minimum_required(VERSION 3.24)
project(SortedSetSLL)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortedSetSLL main.cpp SortedSet.h SortedSet.cpp ShortTest.h ShortTest.cpp ExtendedTest.h ExtendedTest.cpp)
