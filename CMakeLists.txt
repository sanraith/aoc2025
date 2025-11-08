cmake_minimum_required(VERSION 4.0)
project(aoc2025)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Ensures strict conformance (no compiler extensions)

add_executable(aoc2025 src/main.cpp)

if (MSVC)
    add_compile_options(/permissive-)

    # Set warning level 4
    add_compile_options(/W4)

    # Enable signed/unsigned conversion warnings at level 4
    add_compile_options(/w44365)

    # Set external header warning level to 3 (for VS 2019+)
    add_compile_options(/external:W3)

    # Treat warnings as errors
    add_compile_options(/WX)
else()
    # Treat warnings as errors
    add_compile_options(-Werror)
endif()
