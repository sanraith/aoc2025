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
#include <queue>
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

            const auto lines = points
                               | std::views::pairwise
                               | std::views::transform([](const auto& pair) {
                                   return std::pair(std::get<0>(pair), std::get<1>(pair));
                               }) | std::ranges::to<std::vector>();

            // fill edges
            std::set<Point> colored{};
            for (const auto& line : points | std::views::pairwise) {
                const auto& a = std::get<0>(line);
                const auto& b = std::get<1>(line);
                const Point dir{signum(b.x - a.x), signum(b.y - a.y)};
                Point current = a;
                while (current != b) {
                    Point copy = current;
                    colored.insert(copy);
                    current = current + dir;
                }
            }

            // find normals
            const std::map<int, Point> angleToDir = {
                {0, {0, -1}},
                {90, {1, 0}},
                {180, {0, 1}},
                {270, {-1, 0}},
            };
            std::vector<int> normals{};
            auto totalRotation = -getAngle(lines[0]);
            auto prevRotation = 0;
            for (const auto& line : lines) {
                const auto rotation = getAngle(line);
                normals.push_back(rotation);
                totalRotation += rotation - prevRotation;
                prevRotation = rotation;
            }
            const auto normalDiff = signum(totalRotation) * -90;
            for (auto& rotation : normals) { rotation = (rotation + normalDiff + 360) % 360; }
            std::cout << "Total rotation: " << totalRotation << std::endl;

            auto maxArea = -1ll;
            for (int a = 0; a < points.size(); a++) {
                context().progress(a,points.size());
                for (int b = a + 1; b < points.size(); b++) {
                    const auto& rectA = points[a];
                    const auto& rectB = points[b];
                    const auto area = rectArea(rectA, rectB);
                    if (area <= maxArea) { continue; }

                    if (rectA == Point{11, 1} && rectB == Point{7, 3}) {
                        std::cout << "debug" << std::endl;
                    }

                    bool isOutside = false;
                    for (int li = 0; li < lines.size(); li++) {
                        const auto& [lineA, lineB] = lines[li];
                        const auto& normal = normals[li];
                        const auto& normalDir = angleToDir.at((normal + 360) % 360);

                        if (isIntersecting(lineA, lineB, rectA, rectB)
                            //&&                            isIntersecting(lineA + normalDir, lineB + normalDir, rectA, rectB)
                        ) {
                            bool isNormalOutside = false;
                            const auto nLineA = lineA + normalDir;
                            const auto nLineB = lineB + normalDir;
                            const Point lineDir = Point{signum(nLineB.x - nLineA.x), signum(nLineB.y - nLineA.y)};
                            for (Point current = nLineA; current != nLineB; current = current + lineDir) {
                                if (contains(rectA, rectB, current) && !colored.contains(current)) {
                                    isNormalOutside = true;
                                    break;
                                }
                            }
                            if (isNormalOutside) {
                                isOutside = true;
                                break;
                            }
                        }
                    }

                    if (!isOutside) { maxArea = area; }
                }
            }

            return maxArea;
            // 1509986250 too low
            // 1513792010 -- right!!!
            // 182366626

        }

    private:
        struct Point {
            int x{};
            int y{};

            Point operator+(Point const& other) const {
                return Point{x + other.x, y + other.y};
            }

            Point operator-(Point const& other) const {
                return Point{x - other.x, y - other.y};
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


        static int getAngle(std::pair<Point, Point> pair) {
            const auto& [p1, p2] = pair;
            if (p1.x == p2.x) {
                // vertical
                if (p1.y > p2.y) { return 0; }
                if (p1.y < p2.y) { return 180; }
                std::cout << "error" << std::endl;
            }
            else if (p1.y == p2.y) {
                // horizontal
                if (p1.x > p2.x) { return 270; }
                if (p1.x < p2.x) { return 90; }
                std::cout << "error" << std::endl;
            }
            return -1;
        }

        static bool contains(const Point& rectA, const Point& rectB, const Point& p) {
            const auto ax = std::min(rectA.x, rectB.x);
            const auto bx = std::max(rectA.x, rectB.x);
            const auto ay = std::min(rectA.y, rectB.y);
            const auto by = std::max(rectA.y, rectB.y);
            return p.x >= ax && p.x <= bx && p.y >= ay && p.y <= by;
        }

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
            return static_cast<int64_t>(abs(a.x - b.x) + 1) * static_cast<int64_t>(abs(a.y - b.y) + 1);
        }

        static std::vector<Point> parse(const std::string_view input) {
            return getLines(input) | std::views::transform([](const std::string& line) {
                const auto parts = util::split(line, ",");
                return Point{stoi(parts[0]), stoi(parts[1])};
            }) | std::ranges::to<std::vector>();
        }
    };
}
