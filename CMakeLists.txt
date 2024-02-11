cmake_minimum_required(VERSION 2.8)

project(test)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/libsimdpp-2.1
)

#add_executable(test src/main.cpp)
#add_executable(test src/test.cpp)
add_executable(test src/main.cpp)
