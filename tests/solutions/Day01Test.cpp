#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day01.h"
using namespace aoc::year2025;
using namespace aoc::util;

/** Tests for https://adventofcode.com/2025/day/1 */

TEST_CASE("Day01 for example input 1", "[example]") {
    const auto exampleInput1 = R"(L68
L30
R48
L5
R60
L55
L1
L99
R14
L82
)";

    Day01 day{};
    testPart1(day, exampleInput1, 3);
    testPart2(day, exampleInput1, 6);
}

TEST_CASE("Day01 for puzzle input", "[puzzle]") {
    Day01 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 1059);
    testPart2(day, input, 6305);
}
