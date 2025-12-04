#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day04.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/4 */

TEST_CASE("Day04 for example input 1", "[example]") {
    const auto exampleInput1 = R"(..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.")";

    Day04 day{};
    testPart1(day, exampleInput1, 13);
    testPart2(day, exampleInput1, 43);
}

TEST_CASE("Day04 for puzzle input", "[puzzle]") {
    Day04 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 1356);
    testPart2(day, input, 8713);
}
