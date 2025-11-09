#include <catch2/catch_test_macros.hpp>
#include "../../src/solutions/Day01.h"
using namespace aoc::year2025;

auto exampleInput1 = "example";
TEST_CASE("Day01 part 1 example 1", "[example]") {
    REQUIRE(Day01{}.part1(exampleInput1).value == "7");
}

TEST_CASE("Day01 part 2 example 1", "[example]") {
    REQUIRE(Day01{}.part2(exampleInput1).value == "???");
}

// TEST_CASE("Day01 part 1 puzzle input", "[puzzle]") {
//     REQUIRE(Day01{}.part1(exampleInput).value == "7");
// }
// TEST_CASE("Day01 part 2 puzzle input", "[puzzle]") {
//     REQUIRE(Day01{}.part2(exampleInput).value == "???");
// }
