cmake_minimum_required(VERSION 3.15)
project(projects)

set(CMAKE_CXX_STANDARD 14)

add_executable(projects main.cpp heap/BHeap.h heap/BinomHeap.h heap/LeftistHeap.h heap/SkewHeap.h test/runner.h test/utils.h heap/AbstractHeap.h)