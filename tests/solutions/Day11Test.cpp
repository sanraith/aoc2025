#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day11.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/11 */

TEST_CASE ("Day11 for example input 1", "[example]") {
    const auto exampleInput1 = R"(aaa: you hhh
you: bbb ccc
bbb: ddd eee
ccc: ddd eee fff
ddd: ggg
eee: out
fff: out
ggg: out
hhh: ccc fff iii
iii: out
)";

    Day11 day{};
    testPart1(day, exampleInput1, 5);
}

TEST_CASE ("Day11 for example input 2", "[example]") {
    const auto exampleInput1 = R"(svr: aaa bbb
aaa: fft
fft: ccc
bbb: tty
tty: ccc
ccc: ddd eee
ddd: hub
hub: fff
eee: dac
dac: fff
fff: ggg hhh
ggg: out
hhh: out
)";

    Day11 day{};
    testPart2(day, exampleInput1, 2);
}

TEST_CASE ("Day11 for puzzle input", "[puzzle]") {
    Day11 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 649);
    testPart2(day, input, 458948453421420);
}

