#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day10.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/10 */

TEST_CASE("Day10 for example input 1", "[example]") {
    const auto exampleInput1 = R"([.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7})";

    Day10 day{};
    testPart1(day, exampleInput1, 2);
    testPart2(day, exampleInput1, 10);
}

TEST_CASE("Day10 for example input 2", "[example]") {
    const auto exampleInput2 = R"([...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2})";

    Day10 day{};
    testPart1(day, exampleInput2, 3);
    testPart2(day, exampleInput2, 12);
}

TEST_CASE("Day10 for example input 3", "[example]") {
    const auto exampleInput3 = R"([.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5})";

    Day10 day{};
    testPart1(day, exampleInput3, 2);
    testPart2(day, exampleInput3, 11);
}

TEST_CASE("Day10 for puzzle input", "[puzzle]") {
    Day10 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 473);
    // testPart2(day, input, "not_implemented");
}
