add_executable(tests
        solutions/Day01Test.cpp
        solutions/testhelper.h
        solutions/testhelper.cpp
)
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain aoc2025lib)