#pragma once
#include "../util/Solution.h"
using namespace aoc::util;

namespace aoc::year2025 {
    class Day01 final : public Solution {
    public:
        Day01() : Solution("First Day Title") {}
        Result part1(std::string_view input) override;
        Result part2(std::string_view input) override;
    };
}
