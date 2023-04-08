cmake_minimum_required(VERSION 3.16)

project(program)

include_directories(inc)

file(GLOB SRC src/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
