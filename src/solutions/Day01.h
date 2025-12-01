#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <string>
#include <vector>
#include <ranges>

using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/1 */
    class Day01 final : public Solution {
    public:
        Day01() : Solution(2025, 1, "Secret Entrance") {}

        Result part1(const std::string_view input) override {
            const auto steps = parse(input);
            int dial = DIAL_START;
            int password = 0;
            for (const int step : steps) {
                dial = wrap_mod(dial + step, DIAL_SIZE);
                if (dial == 0) { password++; }
            }

            return password;
        }

        Result part2(const std::string_view input) override {
            const auto steps = parse(input);
            int dial = DIAL_START;
            int password = 0;
            for (const int step : steps) {
                const int sign = step < 0 ? -1 : 1;
                const int stepAbs = abs(step);
                for (int i = 0; i < stepAbs; i++) {
                    dial = wrap_mod(dial + sign, DIAL_SIZE);
                    if (dial == 0) { password++; }
                }
            }

            return password;
        }

    private:
        const int DIAL_START = 50;
        const int DIAL_SIZE = 100;

        static std::vector<int> parse(const std::string_view input) {
            const auto lines = getLines(input);
            std::vector<int> numbers{};
            for (const auto& line : lines) {
                const int sign = line[0] == 'L' ? -1 : 1;
                const int clicks = std::stoi(line.substr(1, line.size()));
                numbers.push_back(sign * clicks);
            }
            return numbers;
        }
    };
}
