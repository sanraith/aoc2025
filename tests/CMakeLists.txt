Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.11.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
        solutions/Day01Test.cpp
)
target_link_libraries(tests PRIVATE aoc2025lib Catch2::Catch2WithMain)