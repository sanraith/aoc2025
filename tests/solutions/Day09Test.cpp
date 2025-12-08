#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day09.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/9 */

TEST_CASE ("Day09 for example input 1", "[example]") {
    const auto exampleInput1 = R"(7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
)";

    Day09 day{};
    testPart1(day, exampleInput1, 50);
    testPart2(day, exampleInput1, 24);
}

TEST_CASE ("Day09 for puzzle input", "[puzzle]") {
    Day09 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 4'738'108'384);
    // testPart2(day, input, "not_implemented");
}

