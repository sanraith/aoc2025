#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day__DAY_PADDED__.h"
using namespace aoc::year__YEAR__;

/** Tests for __PUZZLE_URL__ */

TEST_CASE (
"Day__DAY_PADDED__ for example input 1"
,
"[example]"
)
 {
    const auto exampleInput1 = R"(__EXAMPLE_INPUT__)";

    Day__DAY_PADDED__ day{};
    testPart1(day, exampleInput1, __EXAMPLE_RESULT_PART1__);
    testPart2(day, exampleInput1, "not_implemented");
}

TEST_CASE (
"Day__DAY_PADDED__ for puzzle input"
,
"[puzzle]"
)
 {
    Day__DAY_PADDED__ day{};
    const std::string input = getInputReader().readInputFor(day);
    testPart1(day, input, "?");
    testPart2(day, input, "not_implemented");
}