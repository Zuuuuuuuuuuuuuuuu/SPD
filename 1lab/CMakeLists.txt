cmake_minimum_required(VERSION 3.16)

project(zajecia1)

include_directories(inc)

file(GLOB SRC src/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
