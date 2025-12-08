add_executable(tests
        solutions/testhelper.h
        solutions/testhelper.cpp
        solutions/Day01Test.cpp
        solutions/Day02Test.cpp
        solutions/Day03Test.cpp
        solutions/Day04Test.cpp
        solutions/Day05Test.cpp
        solutions/Day06Test.cpp
        solutions/Day07Test.cpp
        solutions/Day08Test.cpp
)
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain aoc2025lib)