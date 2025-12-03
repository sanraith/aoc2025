#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/3 */
    class Day03 final : public Solution {
    public:
        Day03() : Solution(2025, 3, "Lobby") {}

        Result part1(const std::string_view input) override {
            return calculateTotalJoltage(parse(input), 2);
        }

        Result part2(const std::string_view input) override {
            return calculateTotalJoltage(parse(input), 12);
        }

    private:
        static int64_t calculateTotalJoltage(const std::vector<std::vector<int>>& banks, const int digitCount) {
            int64_t joltageSum = 0;
            for (const auto& bank : banks) {
                joltageSum += calculateJoltage(bank, digitCount);
            }
            return joltageSum;
        }

        static int64_t calculateJoltage(const std::vector<int>& bank, const int digitCount) {
            int64_t joltage = 0;
            std::vector<int>::size_type digitIndex = -1;
            for (int remainingDigits = digitCount - 1; remainingDigits >= 0; remainingDigits--) {
                digitIndex = maxIndexOfInRange(bank, digitIndex + 1, bank.size() - remainingDigits);
                joltage = joltage * 10 + bank[digitIndex];
            }
            return joltage;
        }

        static std::vector<int>::size_type maxIndexOfInRange(const std::vector<int>& nums,
                                                             const std::vector<int>::size_type start,
                                                             const std::vector<int>::size_type endExclusive) {
            int max = -1;
            std::vector<int>::size_type maxIndex = -1;
            for (auto i = start; i < endExclusive; i++) {
                if (nums[i] > max) {
                    maxIndex = i;
                    max = nums[i];
                }
            }

            return maxIndex;
        }

        static std::vector<std::vector<int>> parse(const std::string_view input) {
            const auto lines = util::getLines(input);
            std::vector<std::vector<int>> banks{};
            for (const auto& line : lines) {
                std::vector<int> bank{};
                for (const auto c : line) {
                    bank.emplace_back(c - '0');
                }
                banks.emplace_back(bank);
            }
            return banks;
        }
    };
}
