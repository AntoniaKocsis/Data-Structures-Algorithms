cmake_minimum_required(VERSION 3.24)
project(IndexedListDLLA)

set(CMAKE_CXX_STANDARD 20)

add_executable(IndexedListDLLA main.cpp ExtendedTest.cpp ExtendedTest.h ShortTest.cpp ShortTest.h IndexedList.cpp IndexedList.h)
