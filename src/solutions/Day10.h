#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <regex>
#include <string>
#include <algorithm>
#include <bitset>
#include <set>
#include <ranges>
#include <vector>
#include <queue>
#include <execution>
#include <iostream>
#include <mutex>
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
            const auto machines = parse(input);
            // auto sum = 0ll;
            // // for (const auto& machine : machines) {
            // for (int i = 0; i < machines.size(); i++) {
            //     std::cout << i + 1 << "  / " << machines.size() << std::endl;
            //     context().progress(i, machines.size());
            //     const auto& machine = machines[i];
            //     sum += fewestPresses(machine.joltages, machine.buttonVectors);
            // }

            std::mutex m{};
            auto sum = 0ll;
            auto completeCount = 0;
            const auto completeMax = machines.size();
            std::for_each(std::execution::par, machines.begin(), machines.end(), [&](const auto& machine) {
                const auto presses = fewestPresses(machine.joltages, machine.buttonVectors);
                std::lock_guard lock(m);
                sum += presses;
                context().progress(completeCount++, completeMax);
            });

            return sum;
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


        struct JoltageTarget {
            int joltageIndex{};
            std::vector<int> affectingButtonIndices{};
            bool operator<(JoltageTarget const& other) const { return joltageIndex < other.joltageIndex; }
        };

        using Joltage = std::vector<int>;
        using Button = std::vector<int>;
        using NormalizedButton = std::vector<short>; // basically bitmask at this point

        static std::vector<NormalizedButton> sortButtons(const std::vector<NormalizedButton>& normalizedButtons,
                                                         const Joltage& targetJoltage) {
            // Create list of buttons affecting a given joltage index, ordered by count of buttons.
            std::vector<std::pair<int, JoltageTarget>> buttonCountJoltageIndex{};
            for (int i = 0; i < targetJoltage.size(); i++) {
                int sum = 0;
                std::vector<int> buttonIndices{};
                int buttonIndex = 0;
                for (const auto& button : normalizedButtons) {
                    sum += button[i];
                    if (button[i] > 0) { buttonIndices.push_back(buttonIndex); }
                    buttonIndex++;
                }
                buttonCountJoltageIndex.emplace_back(sum, JoltageTarget{i, std::move(buttonIndices)});
            }
            std::ranges::sort(buttonCountJoltageIndex);
            for (const auto& [count,t] : buttonCountJoltageIndex) {
                const auto& [i, buttonIndices] = t;
                // std::cout << count << ", ";
            }
            // std::cout << std::endl;

            std::set<int> seenSet{};
            return buttonCountJoltageIndex | std::views::transform([](const auto& pair) {
                const auto& [count, target] = pair;
                return target.affectingButtonIndices;
            }) | std::views::join | std::views::filter([&seenSet](const int buttonIdx) {
                return seenSet.insert(buttonIdx).second;
            }) | std::views::transform([&normalizedButtons](const auto buttonIdx) {
                return normalizedButtons[buttonIdx];
            }) | std::ranges::to<std::vector>();
        }

        static std::vector<NormalizedButton> normalizeButtons(const std::vector<Button>& buttons,
                                                              const auto size) {
            return buttons | std::views::transform([size](const auto& button) {
                NormalizedButton normalized(size);
                for (const auto bit : button) {
                    normalized[bit] = 1;
                }
                return normalized;
            }) | std::ranges::to<std::vector>();
        }

        static int calcMaxPresses(const NormalizedButton& button, const Joltage& joltage) {
            int joltageMin = INT_MAX;
            for (int i = 0; i < button.size(); i++) {
                if (button[i] > 0) { joltageMin = std::min(joltageMin, joltage[i]); }
            }
            return joltageMin == INT_MAX ? 0 : joltageMin;
        }

        static int calcMinPresses(const std::vector<NormalizedButton>& buttons, const int currentButtonIndex,
                                  const Joltage& remainingJoltage) {
            std::vector<int> maxPressesByButton(buttons.size());
            for (int i = currentButtonIndex + 1; i < buttons.size(); i++) {
                maxPressesByButton[i] = calcMaxPresses(buttons[i], remainingJoltage);
            }

            int minPressCount = 0;
            const auto& currentButton = buttons[currentButtonIndex];
            for (int ji = 0; ji < remainingJoltage.size(); ji++) {
                if (currentButton[ji] == 0) { continue; }
                auto joltage = remainingJoltage[ji];
                for (int bi = currentButtonIndex + 1; bi < buttons.size(); bi++) {
                    if (buttons[bi][ji] == 0) { continue; }
                    const auto maxPresses = maxPressesByButton[bi];
                    joltage = std::max(0, joltage - maxPresses);
                }
                minPressCount = std::max(minPressCount, joltage);
            }

            return minPressCount == INT_MAX ? 0 : minPressCount;
        }

        static bool press(const NormalizedButton& button, Joltage& joltage, const int count = 1) {
            for (int i = 0; i < button.size(); i++) {
                if ((joltage[i] -= button[i] * count) < 0) { return false; }
            }
            return true;
        }

        static int backtrack(const std::vector<NormalizedButton>& normalizedButtons, const Joltage& targetJoltage,
                             Joltage& remainingJoltage,
                             const int buttonIndex = 0,
                             const int currentPressCount = 0,
                             int bestTotalPressCount = INT_MAX) {
            auto previousJoltage = remainingJoltage;
            const Joltage zeroJoltage(targetJoltage.size());
            const auto& button = normalizedButtons[buttonIndex];
            const auto maxPresses = calcMaxPresses(button, remainingJoltage);
            const auto minPresses = calcMinPresses(normalizedButtons, buttonIndex, remainingJoltage);

            if (minPresses > 1) {
                if (!press(button, remainingJoltage, minPresses - 1)) {
                    remainingJoltage = std::move(previousJoltage);
                    return bestTotalPressCount;
                }
            }
            for (int i = minPresses; i <= maxPresses; i++) {
                const auto totalPressCount = currentPressCount + i;
                if (totalPressCount >= bestTotalPressCount) { break; }

                if (i == 0 || press(button, remainingJoltage)) {
                    // std::cout << buttonIndex << ": " << i << "; j: ";
                    // for (const auto j : remainingJoltage) {
                    //     std::cout << j << ", ";
                    // }
                    // std::cout << std::endl;
                    // if (remainingJoltage == std::vector{5, 5, 5, 0, 0} && buttonIndex == 1 && i == 5) {
                    //     std::cout << "\n";
                    // }

                    if (remainingJoltage == zeroJoltage) {
                        // std::cout << "Found: " << totalPressCount << std::endl;
                        if (buttonIndex == normalizedButtons.size() - 1) {
                            remainingJoltage = std::move(previousJoltage);
                            return totalPressCount;
                        }
                        bestTotalPressCount = std::min(bestTotalPressCount, totalPressCount);
                    }
                    else if (buttonIndex < normalizedButtons.size() - 1) {
                        const auto backtrackedCount =
                            backtrack(normalizedButtons, targetJoltage, remainingJoltage, buttonIndex + 1,
                                      totalPressCount, bestTotalPressCount);
                        bestTotalPressCount = std::min(bestTotalPressCount, backtrackedCount);
                    }
                }
                else { break; }
            }

            remainingJoltage = std::move(previousJoltage);
            return bestTotalPressCount;
        }

        static int fewestPresses(const Joltage& targetJoltage,
                                 const std::vector<Button>& origButtons) {
            const auto sortedNormalizedButtons =
                sortButtons(normalizeButtons(origButtons, targetJoltage.size()), targetJoltage);
            // const auto sortedNormalizedButtons = normalizeButtons(origButtons, targetJoltage.size());

            Joltage remainingJoltage = targetJoltage;
            return backtrack(sortedNormalizedButtons, targetJoltage, remainingJoltage);
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
