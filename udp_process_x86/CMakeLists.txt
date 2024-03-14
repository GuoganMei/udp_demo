cmake_minimum_required(VERSION 3.10) 

project(main VERSION 1.0) 

SET(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
aux_source_directory(src SRC)

add_executable(main main.cpp ${SRC})
