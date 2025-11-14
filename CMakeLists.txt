cmake_minimum_required(VERSION 4.0)
project(aoc2025)

# Setup C++ standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Ensures strict conformance (no compiler extensions)

# Setup vcpkg
include(external/bootstrap_vcpkg.cmake)
# Make sure to use the included vcpkg toolchain file. The saved CLion build settings use this by default.
# Otherwise use something like: -DCMAKE_TOOLCHAIN_FILE=..\external\vcpkg\scripts\buildsystems\vcpkg.cmake

find_package(fmt CONFIG REQUIRED)
find_package(curlcpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Main library
add_library(aoc2025lib
        src/util/Result.h
        src/util/Solution.h
        src/util/Context.h
        src/solutions/Day01.cpp
        src/solutions/Day01.h
        src/solutions/index.cpp
        src/solutions/index.h
        src/util/InputReader.cpp
        src/util/InputReader.h
)
target_include_directories(aoc2025lib PUBLIC src)
target_link_libraries(aoc2025lib PRIVATE fmt::fmt)

# Tests
enable_testing()
add_subdirectory(tests)

# Scaffold executable
add_executable(scaffold src/scaffold.cpp
        src/scaffold/AocConfig.cpp
        src/scaffold/AocConfig.h)
target_link_libraries(scaffold PRIVATE
        curlcpp::curlcpp
        fmt::fmt
        nlohmann_json::nlohmann_json
)

# Main executable
add_executable(aoc2025 src/main.cpp)
target_link_libraries(aoc2025 PRIVATE aoc2025lib)

# Compiler-specific settings
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
else ()
    # Treat warnings as errors
    add_compile_options(-Werror)
endif ()
