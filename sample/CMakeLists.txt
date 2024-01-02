cmake_minimum_required(VERSION 3.27)
project(katenginesample)

message("EE ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(sample src/main.cpp)
target_include_directories(sample PRIVATE src/)
target_link_libraries(sample PRIVATE katengine::katengine)