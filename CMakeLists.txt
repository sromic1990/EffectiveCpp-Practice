cmake_minimum_required(VERSION 3.20)

project(EffectiveC++
    VERSION 0.1.0
    DESCRIPTION "A practice project for effective C++ techniques"
    LANGUAGES CXX
)

# Default C++ standrad, can be overidden from presets if needed
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add per-item subdirectories
add_subdirectory(Item2)

# Just to prove it works, print something at configure time
message(STATUS "Configuring ${PROJECT_NAME} with C++ standard ${CMAKE_CXX_STANDARD}")