#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day05.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/5 */

TEST_CASE ("Day05 for example input 1", "[example]") {
    const auto exampleInput1 = R"(3-5
10-14
16-20
12-18

1
5
8
11
17
32
)";

    Day05 day{};
    testPart1(day, exampleInput1, 3);
    testPart2(day, exampleInput1, "not_implemented");
}

TEST_CASE ("Day05 for puzzle input", "[puzzle]") {
    Day05 day{};
    const std::string input = loadPuzzleInput(day);
    // testPart1(day, input, "not_implemented");
    // testPart2(day, input, "not_implemented");
}

