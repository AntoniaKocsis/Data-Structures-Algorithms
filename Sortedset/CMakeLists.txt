cmake_minimum_required(VERSION 3.24)
project(Sortedset)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sortedset App.cpp ExtendedTest.h ExtendedTest.cpp SortedSet.h SortedSet.cpp ShortTest.h ShortTest.cpp SortedSetIterator.h SortedSetIterator.cpp)
