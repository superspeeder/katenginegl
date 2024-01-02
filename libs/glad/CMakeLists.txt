cmake_minimum_required(VERSION 3.27)
project(glad)

message("EE ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(glad src/gl.c include/KHR/khrplatform.h include/glad/gl.h)
target_include_directories(glad PUBLIC include/)

add_library(glad::glad ALIAS glad)
