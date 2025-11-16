#include <catch2/catch_test_macros.hpp>
#include "testhelper.h"
#include "solutions/Day01.h"
using namespace aoc::year2025;

auto exampleInput1 = R"(Multi
line
example)";

TEST_CASE("Day01 for example input 1", "[example]") {
    Day01 day{};
    testPart1(day, exampleInput1, 18);
    testPart2(day, exampleInput1, "not implemented");
}

TEST_CASE("Day01 for puzzle input", "[puzzle]") {
    Day01 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 15000);
    testPart2(day, input, "not implemented");
}
