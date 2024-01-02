cmake_minimum_required(VERSION 3.27)
project(katengine)

message("EE ${CMAKE_CURRENT_SOURCE_DIR}")

find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(katengine src/kat/engine.hpp src/kat/engine.cpp)
target_include_directories(katengine PUBLIC src/ ${Stb_INCLUDE_DIR})
target_link_libraries(katengine PUBLIC glad::glad glfw glm::glm spdlog::spdlog)

add_library(katengine::katengine ALIAS katengine)