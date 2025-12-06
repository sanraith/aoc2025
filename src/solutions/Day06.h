#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <ranges>
#include <regex>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/6 */
    class Day06 final : public Solution {
    public:
        Day06() : Solution(2025, 6, "Trash Compactor") {}

        Result part1(const std::string_view input) override {
            const auto problems = parse(input);
            auto sum = 0ll;
            for (int opIndex = 0; opIndex < problems.operators.size(); opIndex++) {
                const auto& op = problems.operators[opIndex];
                const auto isMultiply = op == "*";
                auto result = isMultiply ? 1ll : 0ll;
                for (int numIndex = 0;numIndex<problems.numbers.size();numIndex++){
                    const auto num = problems.numbers[numIndex][opIndex];
                    if (isMultiply) {
                        result *= num;
                    }
                    else {
                        result += num;
                    }
                }
                sum += result;
            }
            return sum;
        }

        Result part2(const std::string_view input) override {
            return NotImplementedResult;
        }

    private:
        using Operator = std::string;

        struct Problems {
            std::vector<std::vector<int64_t>> numbers{};
            std::vector<Operator> operators{};
        };

        Problems parse(const std::string_view inputView) {
            const auto lines = util::getLines(inputView);
            std::string numOrOpRegex = R"((\d+|[\*+]))";
            std::vector<std::vector<int64_t>> problems{};
            for (int i = 0; i < lines.size() - 1; i++) {
                auto& line = lines[i];
                auto numStrings = captures_from_first_match(line, numOrOpRegex);
                problems.emplace_back(strings_to_ints(numStrings));
            }

            const auto operators = captures_from_first_match(lines[lines.size() - 1], numOrOpRegex);

            return Problems{problems, operators};
        }

        static std::vector<int64_t> strings_to_ints(const std::vector<std::string>& src) {
            std::vector<int64_t> out;
            out.reserve(src.size());
            for (const auto& s : src) out.push_back(std::stoll(s));
            return out;
        }


        static std::vector<std::string> captures_from_first_match(const std::string& text, const std::string& pattern) {
            std::regex re(pattern);
            std::sregex_iterator it(text.begin(), text.end(), re), end;
            std::vector<std::string> out;
            for (; it != end; ++it) {
                // push the first capture group if present, otherwise the whole match
                if (it->size() > 1) out.push_back((*it)[1].str());
                else out.push_back((*it)[0].str());
            }
            return out;
        }
    };
}
