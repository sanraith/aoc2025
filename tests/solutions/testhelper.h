#pragma once
#include <catch2/catch_test_macros.hpp>
#include "util/InputReader.h"
#include "util/Solution.h"
using namespace aoc::util;

inline void testPart(Solution& day, const int part, const std::string_view input, const Result& expected) {
    const Result actualResult = part == 1 ? day.part1(input) : day.part2(input);
    if (actualResult.state != Result::State::NotImplemented) {
        REQUIRE(actualResult.value == expected.value);
    }
}

inline void testPart1(Solution& day, const std::string_view input, const Result& expected) {
    SECTION("solves part 1") { testPart(day, 1, input, expected); }
}

inline void testPart2(Solution& day, const std::string_view input, const Result& expected) {
    SECTION("solves part 2") { testPart(day, 2, input, expected); }
}

inline const InputReader& getInputReader() {
    static const InputReader reader{"../../"};
    return reader;
}
