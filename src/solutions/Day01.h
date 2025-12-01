#pragma once
#include "../util/Solution.h"

#include <string>
#include <vector>
#include <ranges>
#include <cassert>

using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/1 */
    class Day01 final : public Solution {
    public:
        Day01() : Solution(2025, 1, "Secret Entrance") {}

        Result part1(const std::string_view input) override {
            const auto steps = parse(input);
            int dial = 50;
            int password = 0;
            for (const int step : steps) {
                dial = wrap_mod(dial + step, DIAL_SIZE);
                if (dial == 0) { password++; }
            }

            return password;
        }

        Result part2(const std::string_view input) override {
            const auto steps = parse(input);
            int dial = 50;
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
        const int DIAL_SIZE = 100;

        static std::vector<int> parse(std::string_view input) {
            const auto lines = getLines(input);
            std::vector<int> numbers;
            for (const std::string& line : lines) {
                const int sign = line[0] == 'L' ? -1 : 1;
                const int clicks = std::stoi(line.substr(1, line.size()));
                numbers.push_back(sign * clicks);
            }
            return numbers;
        }

        static std::vector<std::string> getLines(std::string_view input) {
            namespace rv = std::ranges::views;
            auto view = input
                        | rv::split('\n')
                        | rv::transform([](auto subStr) {
                            std::string s{std::ranges::begin(subStr), std::ranges::end(subStr)};
                            if (!s.empty() && s.back() == '\r') s.pop_back();
                            return s;
                        })
                        | rv::filter([](const std::string& x) { return !x.empty(); });
            std::vector lines(view.begin(), view.end());
            return lines;
        }

        /** Wraps integer x into a range of 0...m-1 (requires m > 0) */
        template<typename Int>
        constexpr Int wrap_mod(Int num, Int range) {
            static_assert(std::is_integral_v<Int>, "Integral type required");
            assert(range > 0);
            Int r = num % range;
            if (r < 0) r += range;
            return r;
        }
    };
}
