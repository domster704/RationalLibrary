cmake_minimum_required(VERSION 3.24)
project(Rational)

set(CMAKE_CXX_STANDARD 20)

add_executable(doctest rational_doctest.cpp)

target_link_libraries(doctest rationallib)