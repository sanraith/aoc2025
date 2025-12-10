#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <regex>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <ranges>
#include <vector>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/10 */
    class Day10 final : public Solution {
    public:
        Day10() : Solution(2025, 10, "Factory") {}

        Result part1(const std::string_view input) override {
            auto machines = parse(input);
            return NotImplementedResult;
        }

        Result part2(const std::string_view input) override {
            return NotImplementedResult;
        }

    private:
        struct Machine {
            const std::string lights{};
            const std::vector<std::vector<int>> buttons{};
            const std::vector<int> joltages{};
        };

        static std::vector<Machine> parse(const std::string_view input) {
            return getLines(input) | std::views::transform([](auto& line) {
                std::regex partsRe{R"(\[([\.#]+)\] (.+) \{(.+)\})"};
                std::smatch match{};
                std::regex_search(line, match, partsRe);
                auto lightsStr = match[1].str();
                const auto buttonsStr = match[2].str();
                const auto joltageStr = match[3].str();

                const auto buttons = split(buttonsStr, " ") | std::views::transform([](const auto& buttonStr) {
                    return split(std::regex_replace(buttonStr, std::regex(R"([\(\)])"), ""), ",")
                           | std::views::transform([](const auto& numberStr) { return stoi(numberStr); })
                           | std::ranges::to<std::vector>();
                }) | std::ranges::to<std::vector>();
                const auto joltages = split(std::regex_replace(joltageStr, std::regex(R"([\{\}])"), ""), ",")
                                      | std::views::transform([](const auto& numberStr) { return stoi(numberStr); })
                                      | std::ranges::to<std::vector>();

                return Machine{std::move(lightsStr), std::move(buttons), std::move(joltages)};
            }) | std::ranges::to<std::vector>();
        }
    };
}
