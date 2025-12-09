#include <catch2/catch_test_macros.hpp>

#include "testhelper.h"
#include "solutions/Day09.h"
using namespace aoc::year2025;

/** Tests for https://adventofcode.com/2025/day/9 */

TEST_CASE ("Day09 for example input 1", "[example]") {
    const auto exampleInput1 = R"(7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
)";

    Day09 day{};
    testPart1(day, exampleInput1, 50);
    testPart2(day, exampleInput1, 24);
}

TEST_CASE ("Day09 for example input 2", "[example]") {
    const auto exampleInput1 = R"(1,0
3,0
3,6
16,6
16,0
18,0
18,9
13,9
13,7
6,7
6,9
1,9
)";

    Day09 day{};
    testPart2(day, exampleInput1, 30);
}


TEST_CASE ("Day09 for example input 3", "[example]") {
    const auto exampleInput1 = R"(1,1
8,1
8,3
3,3
3,4
8,4
8,9
18,9
18,11
5,11
5,9
4,9
4,11
1,11
1,7
6,7
6,6
1,6
)";

    Day09 day{};
    testPart2(day, exampleInput1, 88);
}

TEST_CASE ("Day09 for example input 4", "[example]") {
    const auto exampleInput1 = R"(1,5
3,5
3,8
7,8
7,5
9,5
9,10
11,10
11,3
6,3
6,7
4,7
4,1
13,1
13,12
1,12
)";

    Day09 day{};
    testPart2(day, exampleInput1, 72);
}



TEST_CASE ("Day09 for puzzle input", "[puzzle]") {
    Day09 day{};
    const std::string input = loadPuzzleInput(day);
    testPart1(day, input, 4'738'108'384);
    testPart2(day, input, 1'513'792'010);
}

