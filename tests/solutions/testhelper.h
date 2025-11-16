#pragma once

#include <catch2/catch_test_macros.hpp>
#include "util/InputReader.h"
#include "util/Solution.h"
using namespace aoc::util;

void testPart1(Solution& day, std::string_view input, const Result& expected);
void testPart2(Solution& day, std::string_view input, const Result& expected);

inline const InputReader& getInputReader() {
    static const AocConfig config = *AocConfig::loadFromDisk();
    static const InputReader reader{config};
    return reader;
}
