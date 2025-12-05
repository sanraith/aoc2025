#pragma once
#include <regex>
#include <string>
#include <cstdint>
#include <algorithm>
#include "util/Solution.h"
#include "util/helpers.h"
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/5 */
    class Day05 final : public Solution {
    public:
        Day05() : Solution(2025, 5, "Cafeteria") {}

        Result part1(const std::string_view input) override {
            const auto [ranges, values] = parse(input);
            int freshCount = 0;
            for (const auto& value : values) {
                for (const auto& [start, end] : ranges) {
                    if (value >= start && value <= end) {
                        freshCount++;
                        break;
                    }
                }
            }
            return freshCount;
        }

        Result part2(const std::string_view input) override {
            auto [ranges, _] = parse(input);
            std::ranges::sort(ranges);

            auto freshCount = 0ll;
            auto prevEnd = -1ll;
            for (auto& [start, end] : ranges) {
                end += 1; // make end exclusive
                if (start < prevEnd) { start = prevEnd; }
                if (start > end || end < prevEnd) {
                    start = end = prevEnd;
                }
                freshCount += end - start;
                prevEnd = end;
            }

            return freshCount;
        }

    private:
        struct Data {
            std::vector<std::pair<int64_t, int64_t>> ranges{};
            std::vector<int64_t> values{};
        };

        static Data parse(const std::string_view inputView) {
            const std::regex re(R"(([\s\S]*)\r?\n\r?\n([\s\S]*))");
            std::smatch match{};
            std::string input{inputView};
            std::regex_search(input, match, re);

            const auto strRanges = util::getLines(match[1].str());
            const auto strValues = util::getLines(match[2].str());
            std::vector<std::pair<int64_t, int64_t>> ranges{};
            for (const auto& strRange : strRanges) {
                auto parts = util::split(strRange, "-");
                ranges.emplace_back(std::stoll(parts[0]), std::stoll(parts[1]));
            }

            std::vector<int64_t> values{};
            for (const auto& strValue : strValues) {
                values.push_back(std::stoll(strValue));
            }

            return Data{ranges, values};
        }
    };
}
