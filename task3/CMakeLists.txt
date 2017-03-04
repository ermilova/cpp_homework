cmake_minimum_required(VERSION 3.6)
project(task3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES rational.h rational.cpp)

add_library(rational rational.cpp rational.h)

install(TARGETS rational DESTINATION lib/rational)
install (FILES rational.h DESTINATION include/rational)
install (FILES rational.cpp DESTINATION include/rational)
