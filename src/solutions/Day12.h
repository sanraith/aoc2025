#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <regex>
#include <ranges>
#include <vector>
#include <algorithm>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/12 */
    class Day12 final : public Solution {
    public:
        Day12() : Solution(2025, 12, "Christmas Tree Farm") {}

        Result part1(const std::string_view input) override {
            const auto [shapes, regions] = parse(input);
            const auto maxShapeWith = std::ranges::max(shapes, {}, &Shape::width).width;
            const auto maxShapeHeight = std::ranges::max(shapes, {}, &Shape::height).height;

            auto validRegionCount = 0;
            for (const auto& [width, height, shapeCounts] : regions) {
                const auto nonOverlappingShapeSpace = (width / maxShapeWith) * (height / maxShapeHeight);
                const auto requiredShapeCount = std::ranges::fold_left(shapeCounts, 0, std::plus{});

                if (requiredShapeCount <= nonOverlappingShapeSpace) { validRegionCount++; }
                else {
                    const auto regionSize = width * height;
                    auto minimumRegionSize = 0;
                    for (int i = 0; i < shapeCounts.size(); i++) {
                        minimumRegionSize += shapes[i].netSize * shapeCounts[i];
                    }

                    if (regionSize >= minimumRegionSize) {
                        return Result{"not solved for non-trivial input", Result::State::Failure};
                    }
                }
            }
            return validRegionCount;
        }

        Result part2(const std::string_view input) override {
            return "*";
        }

    private:
        static constexpr char TILE_OCCUPIED = '#';
        static constexpr char TILE_SPACE = '.';

        struct Shape {
            int index{};
            int width{};
            int height{};
            int netSize{};
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
                auto lines = getLines(shapeMatch[2].str());
                const auto netSize = std::ranges::fold_left(lines, 0, [](const auto acc, const auto& line) {
                    return acc + std::count(line.begin(), line.end(), TILE_OCCUPIED);
                });
                shapes.push_back(Shape{
                    stoi(shapeMatch[1].str()), static_cast<int>(lines[0].size()), static_cast<int>(lines.size()),
                    static_cast<int>(netSize), std::move(lines)
                });
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
