#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day02.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/2 */

TEST_CASE("Day02 for example input 1", "[example]") {
    const auto exampleInput1 =
        R"(11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124)";

    Day02 day{};
    testPart1(day, exampleInput1, 1227775554);
    testPart2(day, exampleInput1, 4174379265);
}

TEST_CASE("Day02 for puzzle input", "[puzzle]") {
    Day02 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 40055209690);
    testPart2(day, input, 50857215650);
}

