cmake_minimum_required(VERSION 3.27)
project(katengine)

message("EE ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(libs)
add_subdirectory(engine)
add_subdirectory(sample)