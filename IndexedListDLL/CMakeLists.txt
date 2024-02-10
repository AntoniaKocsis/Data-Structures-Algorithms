cmake_minimum_required(VERSION 3.24)
project(IndexedListDLL)

set(CMAKE_CXX_STANDARD 20)

add_executable(IndexedListDLL main.cpp IndexedList.h IndexedList.cpp ShortTest.cpp ExtendedTest.cpp)
