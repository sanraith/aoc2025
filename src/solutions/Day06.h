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
            for (int opIndex = 0; opIndex < static_cast<int>(problems.operators.size()); opIndex++) {
                const auto& op = problems.operators[opIndex];
                const auto isMultiply = op.op == "*";
                auto result = isMultiply ? 1ll : 0ll;
                for (int numIndex = 0; numIndex < problems.numbers.size(); numIndex++) {
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

        Result part2(const std::string_view inputView) override {
            const auto lines = util::getLines(inputView);
            std::string numOrOpRegex = R"(([\*+]))";
            std::vector<std::vector<int64_t>> problems{};
            std::regex re(numOrOpRegex);
            auto text = lines.back();
            std::sregex_iterator it(text.begin(), text.end(), re), end;
            std::vector<Operator> operators;
            for (; it != end; ++it) {
                // capture operator string and its position within the line
                const size_t pos = static_cast<size_t>((*it).position());
                std::string opStr;
                if (it->size() > 1) opStr = (*it)[1].str();
                else opStr = (*it)[0].str();
                operators.push_back(Operator{opStr, pos});
            }

            auto sum = 0ll;
            for (int opIndex = 0; opIndex < operators.size(); opIndex++) {
                const auto [op, start] = operators[opIndex];
                const auto isMultiply = (op == "*");
                auto result = isMultiply ? 1ll : 0ll;
                const auto endEx = opIndex < operators.size() - 1 ? operators[opIndex + 1].pos - 1 : lines[0].length();
                for (auto numCol = start; numCol < endEx; numCol++) {
                    std::string numStr{};
                    for (auto numLine = 0; numLine < lines.size() - 1; numLine++) {
                        numStr.push_back(lines[numLine][numCol]);
                    }
                    const auto num = std::stoll(numStr);
                    if (isMultiply) { result *= num; }
                    else { result += num; }
                }
                sum += result;
            }

            return sum;
        }

    private:
        struct Operator {
            std::string op;
            size_t pos = 0;
        };

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


            const auto opStrings = captures_from_first_match(lines[lines.size() - 1], numOrOpRegex);
            std::vector<Operator> operators;
            operators.reserve(opStrings.size());
            for (size_t i = 0; i < opStrings.size(); ++i) {
                // fall back to using the index as a position if we don't parse positions elsewhere
                operators.push_back(Operator{opStrings[i], i});
            }

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
