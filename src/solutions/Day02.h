#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include "cmath"
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/2 */
    class Day02 final : public Solution {
    public:
        Day02() : Solution(2025, 2, "Gift Shop") {}

        Result part1(const std::string_view input) override {
            int64_t sum = 0;
            const auto ranges = parse(input);
            for (const auto& [start, end] : ranges) {
                for (auto num = start; num <= end; num++) {
                    const auto digits = static_cast<int>(ceil(log10(num)));
                    if (digits > 1 && digits % 2 == 0 && hasPatternOfLength(num, digits / 2)) {
                        sum += num;
                    }
                }
            }
            return sum;
        }

        Result part2(const std::string_view input) override {
            int64_t sum = 0;
            const auto ranges = parse(input);
            for (const auto& [start, end] : ranges) {
                for (auto num = start; num <= end; num++) {
                    if (hasPattern(num)) { sum += num; }
                }
            }
            return sum;
        }

    private:
        static std::vector<std::pair<int64_t, int64_t>> parse(const std::string_view input) {
            std::vector<std::pair<int64_t, int64_t>> ranges{};
            const auto rangesStr = util::split(input, ",");
            for (const auto& range : rangesStr) {
                const auto parts = util::split(range, "-");
                const int64_t start = std::stoll(parts[0]);
                const int64_t end = std::stoll(parts[1]);
                ranges.emplace_back(start, end);
            }
            return ranges;
        }

        static bool hasPattern(const int64_t num) {
            const auto maxDigits = static_cast<int>(ceil(log10(num)));
            const auto maxPatternDigits = maxDigits / 2;
            for (int digits = maxPatternDigits; digits > 0; digits--) {
                if (maxDigits % digits == 0 && hasPatternOfLength(num, digits)) { return true; }
            }
            return false;
        }

        static bool hasPatternOfLength(int64_t num, const int length) {
            const auto size = static_cast<int64_t>(pow(10, length));
            const auto pattern = num % size;
            while (num / size % size == pattern) {
                num = num / size;
            }
            return num == pattern;
        }
    };
}
