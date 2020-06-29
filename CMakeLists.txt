cmake_minimum_required(VERSION 3.10)
project(bloomFilter)

set(CMAKE_CXX_STANDARD 14)

add_executable(bloom bloomFilter.cpp fnv.h)