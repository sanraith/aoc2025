#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day08.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/8 */

TEST_CASE("Day08 for example input 1", "[example]") {
    const auto exampleInput1 = R"(162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689
)";

    Day08 day{};
    day.setPart1ConnectCount(10);
    testPart1(day, exampleInput1, 40);
    testPart2(day, exampleInput1, 25272);
}

TEST_CASE("Day08 for puzzle input", "[puzzle]") {
    Day08 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 135169);
    testPart2(day, input, 302133440);
}
