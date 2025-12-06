#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day06.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/6 */

TEST_CASE ("Day06 for example input 1", "[example]") {
    const auto exampleInput1 = R"(123 328  51 64
 45 64  387 23
  6 98  215 314
*   +   *   +
)";

    Day06 day{};
    testPart1(day, exampleInput1, 4277556);
    testPart2(day, exampleInput1, 3263827);
}

TEST_CASE ("Day06 for puzzle input", "[puzzle]") {
    Day06 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 4951502530386);
    // testPart2(day, input, "not_implemented");
}

