cmake_minimum_required(VERSION 3.24)
project(SLL)

set(CMAKE_CXX_STANDARD 20)

add_executable(SLL main.cpp SLL.h DLL.h BinaryTree.h BinarySearchTree.h SLLA.h Queue.h)
