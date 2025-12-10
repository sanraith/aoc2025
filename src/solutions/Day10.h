#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <regex>
#include <string>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <string>
#include <ranges>
#include <vector>
#include <queue>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/10 */
    class Day10 final : public Solution {
    public:
        Day10() : Solution(2025, 10, "Factory") {}

        Result part1(const std::string_view input) override {
            const auto machines = parse(input);
            auto sum = 0ll;
            for (const auto& machine : machines) {
                sum += fewestPresses(machine.lights, machine.buttons);
            }
            return sum;
        }

        Result part2(const std::string_view input) override {
            return NotImplementedResult;
        }

    private:
        static constexpr int MAX_BITS = 32;
        static constexpr char LIGHT_ON = '#';
        static constexpr char LIGHT_OFF = '.';
        using NumericBitSet = unsigned long;
        using LightBitSet = std::bitset<MAX_BITS>;

        struct Machine {
            const std::string lightsStr{};
            const LightBitSet lights{};
            const std::vector<std::vector<int>> buttonVectors{};
            const std::vector<LightBitSet> buttons{};
            const std::vector<int> joltages{};
        };

        static int fewestPresses(const LightBitSet& target, const std::vector<LightBitSet>& buttons) {
            if (target == LightBitSet{}) { return 0; }
            std::set<NumericBitSet> visited{};
            std::queue<std::pair<int, LightBitSet>> queue{};
            queue.emplace(0, LightBitSet{});

            while (!queue.empty()) {
                const auto [count, lights] = queue.front();
                queue.pop();
                if (!visited.insert(lights.to_ulong()).second) { continue; }

                const auto nextCount = count + 1;
                for (const auto& button : buttons) {
                    const auto next = lights ^ button;
                    if (next == target) { return nextCount; }
                    if (!visited.contains(next.to_ulong())) { queue.emplace(nextCount, next); }
                }
            }

            return -1;
        }

        static std::vector<Machine> parse(const std::string_view input) {
            return getLines(input) | std::views::transform([](auto& line) {
                std::regex partsRegex{R"(\[([\.#]+)\] (.+) \{(.+)\})"};
                std::smatch match{};
                std::regex_search(line, match, partsRegex);

                auto lightsStr = match[1].str();
                const auto buttonsStr = match[2].str();
                const auto joltageStr = match[3].str();

                LightBitSet bitLights{};
                for (int i = 0; i < lightsStr.size(); i++) {
                    const auto c = lightsStr[i];
                    bitLights.set(i, c == LIGHT_ON);
                }

                const auto buttons = split(buttonsStr, " ") | std::views::transform([](const auto& buttonStr) {
                    return split(std::regex_replace(buttonStr, std::regex(R"([\(\)])"), ""), ",")
                           | std::views::transform([](const auto& numberStr) { return stoi(numberStr); })
                           | std::ranges::to<std::vector>();
                }) | std::ranges::to<std::vector>();
                const auto bitButtons = buttons | std::views::transform([](const auto& button) {
                    LightBitSet bitButton{};
                    for (const int bitIndex : button) { bitButton.set(bitIndex); }
                    return bitButton;
                }) | std::ranges::to<std::vector>();

                const auto joltages = split(joltageStr, ",")
                                      | std::views::transform([](const auto& numberStr) { return stoi(numberStr); })
                                      | std::ranges::to<std::vector>();

                return Machine{
                    std::move(lightsStr), std::move(bitLights),
                    std::move(buttons), std::move(bitButtons),
                    std::move(joltages)
                };
            }) | std::ranges::to<std::vector>();
        }
    };
}
