#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <regex>
#include <ranges>
#include <vector>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/12 */
    class Day12 final : public Solution {
    public:
        Day12() : Solution(2025, 12, "Christmas Tree Farm") {}

        Result part1(const std::string_view input) override {
            const auto data = parse(input);
            return NotImplementedResult;
        }

        Result part2(const std::string_view input) override {
            return NotImplementedResult;
        }

    private:
        struct Shape {
            int index{};
            std::vector<std::string> lines{};
        };

        struct Region {
            int width{};
            int height{};
            std::vector<int> shapeCounts{};
        };

        struct Data {
            std::vector<Shape> shapes{};
            std::vector<Region> regions{};
        };

        static Data parse(const std::string_view inputView) {
            const std::regex partsRegex{R"(([\s\S]+?)(?:(?:\n|\r\n){2}(?=\d+x))([\s\S]+))"};
            const std::string input{inputView};
            std::smatch partsMatch{};
            std::regex_search(input, partsMatch, partsRegex);
            const auto shapesStr = partsMatch[1].str();
            const auto regionsStr = partsMatch[2].str();

            std::vector<Shape> shapes{};
            const std::regex shapeRegex{R"((\d+):(?:\n|\r\n)((?:[#\.]+(?:\n|\r\n)?)+))"};
            for (std::sregex_iterator it(shapesStr.begin(), shapesStr.end(), shapeRegex), end; it != end; ++it) {
                const std::smatch& shapeMatch = *it;
                shapes.push_back(Shape{stoi(shapeMatch[1].str()), getLines(shapeMatch[2].str())});
            }

            std::vector<Region> regions{};
            const std::regex regionRegex{R"((\d+)x(\d+): (.+))"};
            for (const auto& line : getLines(regionsStr)) {
                std::smatch regionMatch{};
                std::regex_search(line, regionMatch, regionRegex);
                const auto width = stoi(regionMatch[1].str());
                const auto height = stoi(regionMatch[2].str());
                auto shapeCounts = split(regionMatch[3].str(), " ")
                                   | std::views::transform([](const auto& numStr) { return stoi(numStr); })
                                   | std::ranges::to<std::vector>();
                regions.push_back(Region{width, height, std::move(shapeCounts)});
            }

            return {std::move(shapes), std::move(regions)};
        }
    };
}
