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
        src/solutions/index.cpp
        src/solutions/index.h
        src/solutions/Day01.h
        src/solutions/Day02.h
        src/solutions/Day03.h
        src/solutions/Day04.h
        src/solutions/Day05.h
        src/solutions/Day06.h
        src/util/CachedAocDataLoader.cpp
        src/util/CachedAocDataLoader.h
        src/util/AocConfig.cpp
        src/util/AocConfig.h
        src/util/SolutionRunner.cpp
        src/util/SolutionRunner.h
        src/util/helpers.h
        src/util/helpers.cpp
)
target_include_directories(aoc2025lib PUBLIC src)
target_link_libraries(aoc2025lib PRIVATE
        curlcpp::curlcpp
        fmt::fmt
        nlohmann_json::nlohmann_json
)

# Tests
enable_testing()
add_subdirectory(tests)

# Scaffold executable
add_executable(scaffold src/scaffold.cpp)
target_link_libraries(scaffold PRIVATE aoc2025lib)
target_link_libraries(scaffold PRIVATE
        fmt::fmt
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
