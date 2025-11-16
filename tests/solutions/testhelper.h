#pragma once

#include <catch2/catch_test_macros.hpp>

#include "util/CachedAocDataLoader.h"
#include "util/Solution.h"
using namespace aoc::util;

void testPart1(Solution& day, std::string_view input, const Result& expected);
void testPart2(Solution& day, std::string_view input, const Result& expected);

template<DerivedFromSolution T>
std::string loadPuzzleInput(const T& day) {
    static const CachedAocDataLoader reader{AocConfig::loadFromDisk().value()};
    const auto inputOpt = reader.loadPuzzleInput(day);
    if (inputOpt) { return *inputOpt; }
    throw std::runtime_error(
        "Failed to load puzzle input for " + std::to_string(day.year()) + "-" + std::to_string(day.day()));
}

