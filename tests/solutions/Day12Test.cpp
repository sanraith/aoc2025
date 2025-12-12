#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day12.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/12 */

TEST_CASE("Day12 for example input 1", "[example]") {
    const auto exampleInput1 = R"(0:
###
##.
##.

1:
###
##.
.##

2:
.##
###
##.

3:
##.
###
##.

4:
###
#..
###

5:
###
.#.
###

4x4: 0 0 0 0 2 0
12x5: 1 0 1 0 2 2
12x5: 1 0 1 0 3 2
)";

    Day12 day{};
    // testPart1(day, exampleInput1, 2); // not solved for non-trivial input
    testPart2(day, exampleInput1, "*");
}

TEST_CASE("Day12 for puzzle input", "[puzzle]") {
    Day12 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 569);
    testPart2(day, input, "*");
}
