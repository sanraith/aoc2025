#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <ranges>
#include <vector>
#include <numeric>
#include <functional>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/9 */
    class Day09 final : public Solution {
    public:
        Day09() : Solution(2025, 9, "Movie Theater") {}

        Result part1(const std::string_view input) override {
            const auto points = parse(input);
            auto maxArea = -1ll;
            for (int a = 0; a < points.size(); a++) {
                for (int b = a + 1; b < points.size(); b++) {
                    maxArea = std::max(maxArea, rectArea(points[a], points[b]));
                }
            }
            return maxArea;
        }

        Result part2(const std::string_view input) override {
            auto pointsInput = parse(input);
            pointsInput.push_back(pointsInput[0]);
            const auto points = pointsInput;

            auto maxArea = -1ll;
            for (int a = 0; a < points.size(); a++) {
                for (int b = a + 1; b < points.size(); b++) {
                    const auto& rectA = points[a];
                    const auto& rectB = points[b];

                    // std::cout << rectA << " - " << rectB << std::endl;
                    //
                    // if (rectA == Point{11, 1} && rectB == Point{7, 3}) {
                    //     std::cout << "";
                    // }

                    // ToDo wrong solution, need to find rectangle of red+green, not rect without additional reds
                    const auto linePairView = points | std::views::pairwise;
                    const bool hasIntersecting =
                        std::ranges::any_of(linePairView, [rectA, rectB](const auto& line) {
                            const auto& lineA = std::get<0>(line);
                            const auto& lineB = std::get<1>(line);
                            if (lineA == rectA || lineA == rectB || lineB == rectA || lineB == rectB) { return false; }
                            return isIntersecting(lineA, lineB, rectA, rectB);
                        });

                    if (!hasIntersecting) {
                        maxArea = std::max(maxArea, rectArea(rectA, rectB));
                    }
                }
            }

            return maxArea;
            // 1509986250 too low
        }

    private:
        struct Point {
            int x{};
            int y{};

            Point operator+(Point const& other) const {
                return Point{x + other.x, y + other.y};
            }

            bool operator<(Point const& other) const {
                if (x != other.x) return x < other.x;
                return y < other.y;
            }

            bool operator==(Point const& other) const {
                return x == other.x && y == other.y;
            }

            friend std::ostream& operator<<(std::ostream& os, Point const& p) {
                return os << "(" << p.x << "," << p.y << ")";
            }
        };

        static bool isIntersecting(const Point& lineAIn, const Point& lineBIn, const Point& rectAIn,
                                   const Point& rectBIn) {
            const auto lax = lineAIn.x < lineBIn.x ? lineAIn.x : lineBIn.x;
            const auto lbx = lineAIn.x < lineBIn.x ? lineBIn.x : lineAIn.x;
            const auto rax = rectAIn.x < rectBIn.x ? rectAIn.x : rectBIn.x;
            const auto rbx = rectAIn.x < rectBIn.x ? rectBIn.x : rectAIn.x;

            const auto lay = lineAIn.y < lineBIn.y ? lineAIn.y : lineBIn.y;
            const auto lby = lineAIn.y < lineBIn.y ? lineBIn.y : lineAIn.y;
            const auto ray = rectAIn.y < rectBIn.y ? rectAIn.y : rectBIn.y;
            const auto rby = rectAIn.y < rectBIn.y ? rectBIn.y : rectAIn.y;

            bool result = false;
            if (lay == lby && lay >= ray && lay <= rby) {
                // horizontal
                // result = (lax <= rax && lbx >= rax) || (lax <= rbx && lbx >= rbx);
                result = (lax <= rax && lbx >= rax) || (lax <= rbx && lbx >= rbx) || (lax >= rax && lbx <= rbx);
            }
            else if (lax == lbx && lax >= rax && lax <= rbx) {
                // vertical
                result = (lay <= ray && lby >= ray) || (lay <= rby && lby >= rby) || (lay >= ray && lby <= rby);
            }
            return result;
        }

        static int64_t rectArea(const Point& a, const Point& b) {
            return static_cast<int64_t>(abs(a.x - b.x) + 1) * abs(a.y - b.y + 1);
        }

        static std::vector<Point> parse(const std::string_view input) {
            return getLines(input) | std::views::transform([](const std::string& line) {
                const auto parts = util::split(line, ",");
                return Point{stoi(parts[0]), stoi(parts[1])};
            }) | std::ranges::to<std::vector>();
        }
    };
}
