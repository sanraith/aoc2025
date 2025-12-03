#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day03.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/3 */

TEST_CASE("Day03 for example input 1", "[example]") {
    const auto exampleInput1 = R"(987654321111111
811111111111119
234234234234278
818181911112111
)";

    Day03 day{};
    testPart1(day, exampleInput1, 357);
    testPart2(day, exampleInput1, 3121910778619);
}

TEST_CASE("Day03 for puzzle input", "[puzzle]") {
    Day03 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 17166);
    testPart2(day, input, 169077317650774);
}
