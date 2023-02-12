cmake_minimum_required(VERSION 3.24)
project(Rational)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_subdirectory(rationallib)
add_subdirectory(tests)

add_executable(Rational main.cpp)

target_link_libraries(Rational rationallib)