cmake_minimum_required(VERSION 3.27)
project(katengine)

message("EE ${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Stb REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(katengine src/kat/engine.hpp src/kat/engine.cpp
        src/kat/window.cpp
        src/kat/window.hpp
        src/kat/signals/signals.cpp
        src/kat/signals/signals.hpp
        src/kat/renderer/renderer.cpp
        src/kat/renderer/renderer.hpp
        src/kat/color.cpp
        src/kat/color.hpp
        src/input_manager.cpp
        src/input_manager.hpp)
target_include_directories(katengine PUBLIC src/ ${Stb_INCLUDE_DIR})
target_link_libraries(katengine PUBLIC glad::glad glm::glm spdlog::spdlog opengl32.lib)

target_compile_features(katengine PUBLIC cxx_std_23)

add_library(katengine::katengine ALIAS katengine)