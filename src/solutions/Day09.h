#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <ranges>
#include <vector>
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
            const auto points = parse(input);
            // make it continuous by re-adding the first point at the end
            auto pointsContinuous = points;
            pointsContinuous.push_back(pointsContinuous[0]);
            const auto edges = pointsContinuous
                               | std::views::pairwise
                               | std::views::transform([](const auto& pair) {
                                   return std::pair(std::get<0>(pair), std::get<1>(pair));
                               }) | std::ranges::to<std::vector>();

            // fill edges
            std::set<Point> edgePoints{};
            for (const auto& [a,b] : edges) {
                const Point dir = (b - a).signum();
                for (Point p = a; p != b; p = p + dir) { edgePoints.insert(p); }
            }

            // find normals
            const auto normals = findNormals(edges);

            // find the largest area
            auto maxArea = -1ll;
            for (int a = 0; a < points.size(); a++) {
                context().progress(a, points.size());
                for (int b = a + 1; b < points.size(); b++) {
                    const auto& rectA = points[a];
                    const auto& rectB = points[b];
                    const auto area = rectArea(rectA, rectB);
                    if (area <= maxArea) { continue; }
                    if (!isRectOutside(rectA, rectB, edges, edgePoints, normals)) { maxArea = area; }
                }
            }

            return maxArea;
        }

    private:
        struct Point {
            int x{};
            int y{};

            [[nodiscard]] Point signum() const { return {util::signum(x), util::signum(y)}; }

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

        static std::vector<Point> findNormals(std::vector<std::pair<Point, Point>> lines) {
            auto norm360 = [](const int a) -> int { return (a % 360 + 360) % 360; };
            auto signedDelta = [&](const int from, const int to) -> int {
                int d = norm360(to - from);
                if (d > 180) d -= 360;
                return d;
            };
            const auto rotations = lines
                                   | std::views::transform([](const auto line) { return getAngle(line); })
                                   | std::ranges::to<std::vector>();
            int totalRotation = 0;
            for (size_t i = 1; i < rotations.size(); ++i) totalRotation += signedDelta(rotations[i - 1], rotations[i]);
            if (!rotations.empty()) totalRotation += signedDelta(rotations.back(), rotations.front());
            const auto normalDiff = totalRotation > 0 ? -90 : 90;

            const std::map<int, Point> angleToDir = {
                {0, {0, -1}},
                {90, {1, 0}},
                {180, {0, 1}},
                {270, {-1, 0}},
            };

            return rotations | std::views::transform([normalDiff,angleToDir,norm360](const auto rotation) {
                return angleToDir.at(norm360(rotation + normalDiff));
            }) | std::ranges::to<std::vector>();
        }

        static bool isRectOutside(const Point& rectA, const Point& rectB,
                                  const std::vector<std::pair<Point, Point>>& lines,
                                  const std::set<Point>& edge,
                                  const std::vector<Point>& normals) {
            bool isOutside = false;
            for (int li = 0; li < lines.size(); li++) {
                const auto& [lineA, lineB] = lines[li];
                const Point& normalDir = normals[li];

                if (isIntersecting(lineA, lineB, rectA, rectB)) {
                    // Check points on a line just outside the current line, but only within the rectangle.
                    // If any of them are not on the colored edges, they have to be outside.
                    const Point nLineA = lineA + normalDir;
                    const Point nLineB = lineB + normalDir;
                    const Point lineDir = (nLineB - nLineA).signum();
                    for (Point p = nLineA; p != nLineB; p = p + lineDir) {
                        if (contains(rectA, rectB, p) && !edge.contains(p)) {
                            isOutside = true;
                            break;
                        }
                    }
                    if (isOutside) { break; }
                }
            }

            return isOutside;
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
