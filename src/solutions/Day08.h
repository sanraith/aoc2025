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
    /** Solution for https://adventofcode.com/2025/day/8 */
    class Day08 final : public Solution {
    public:
        Day08() : Solution(2025, 8, "Playground") {}

        void setPart1ConnectCount(const int count) { _part1ConnectCount = count; }

        Result part1(const std::string_view input) override {
            const auto connectCount = _part1ConnectCount >= 0 ? _part1ConnectCount : 1000;
            const auto points = parse(input);
            const auto distPointPairs = sortedPairsByDistance(points);

            std::map<Point, SharedCircuit> circuitsByPoint{};
            int connected = 0;
            for (int i = 0; i < connectCount; i++) {
                context().progress(i, connectCount);
                const auto& [dist, pair] = distPointPairs[i];
                const auto& [a,b] = pair;
                const auto [connectedChg, _] = connect(a, b, circuitsByPoint);
                connected += connectedChg;
            }

            auto circuits = circuitsByPoint
                            | std::views::values
                            | std::ranges::to<std::set>()
                            | std::ranges::to<std::vector>();
            std::ranges::sort(circuits, std::ranges::greater{},
                              [](const SharedCircuit& sc) { return sc->size(); });
            circuits = circuits | std::views::take(3) | std::ranges::to<std::vector>();
            const auto result = std::accumulate(circuits.begin(), circuits.end(), 1ll,
                                                [](const int64_t a, const SharedCircuit& x) {
                                                    return a * static_cast<int64_t>(x->size());
                                                });
            return result;
        }

        Result part2(const std::string_view input) override {
            const auto points = parse(input);
            const auto distPointPairs = sortedPairsByDistance(points);

            std::map<Point, SharedCircuit> circuitsByPoint{};
            int circuitCount = static_cast<int>(points.size());
            std::pair<Point, Point> lastPair{};
            for (int i = 0; i < distPointPairs.size(); i++) {
                context().progress(i, distPointPairs.size());
                const auto& [dist, pair] = distPointPairs[i];
                const auto [_, circuitChg] = connect(pair.first, pair.second, circuitsByPoint);
                circuitCount += circuitChg;
                if (circuitCount == 1) {
                    lastPair = pair;
                    break;
                }
            }

            return lastPair.first.x * lastPair.second.x;
        }

    private:
        int _part1ConnectCount{-1};

        using CoordInt = int64_t;

        struct Point {
            CoordInt x{};
            CoordInt y{};
            CoordInt z{};

            [[nodiscard]] double euclideanDistance(const Point& other) const {
                return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
            }

            Point operator+(Point const& other) const {
                return Point{x + other.x, y + other.y, z + other.z};
            }

            bool operator<(Point const& other) const {
                if (x != other.x) return x < other.x;
                if (y != other.y) return y < other.y;
                return z < other.z;
            }

            bool operator==(Point const& other) const {
                return x == other.x && y == other.y && z == other.z;
            }

            friend std::ostream& operator<<(std::ostream& os, Point const& p) {
                return os << "(" << p.x << "," << p.y << "," << p.z << ")";
            }
        };

        using Circuit = std::set<Point>;
        using SharedCircuit = std::shared_ptr<Circuit>;

        static std::vector<std::pair<double, std::pair<Point, Point>>>
        sortedPairsByDistance(const std::vector<Point>& points) {
            std::vector<std::pair<double, std::pair<Point, Point>>> distPointPairs{};
            distPointPairs.reserve((points.size() * points.size() - 1) / 2);
            for (int a = 0; a < points.size(); a++) {
                for (int b = a + 1; b < points.size(); b++) {
                    const auto aPoint = points[a];
                    const auto bPoint = points[b];
                    distPointPairs.push_back({aPoint.euclideanDistance(bPoint), {aPoint, bPoint}});
                }
            }
            std::ranges::sort(distPointPairs);
            return distPointPairs;
        }

        static std::pair<int, int> connect(const Point& a, const Point& b,
                                           std::map<Point, SharedCircuit>& circuitsByPoint) {
            int connectedChg = 0;
            int circuitsChg = 0;
            const bool containsA = circuitsByPoint.contains(a);
            const bool containsB = circuitsByPoint.contains(b);
            if (!containsA && !containsB || containsA != containsB) {
                // at most one point is part of a circuit
                const auto circuit =
                    containsA ? circuitsByPoint[a] : containsB ? circuitsByPoint[b] : std::make_shared<Circuit>();
                circuit->insert(a);
                circuit->insert(b);
                circuitsByPoint[a] = circuit;
                circuitsByPoint[b] = circuit;
                connectedChg++;
                circuitsChg--;
            }
            else {
                // both points are part of a circuit
                auto sourceCircuit = circuitsByPoint[b];
                const auto targetCircuit = circuitsByPoint[a];
                if (sourceCircuit != targetCircuit) {
                    // Merge them to the first one otherwise.
                    for (const auto p : *sourceCircuit) {
                        targetCircuit->insert(p);
                        circuitsByPoint[p] = targetCircuit;
                    }
                    sourceCircuit.reset();
                    connectedChg++;
                    circuitsChg--;
                }
            }
            return {connectedChg, circuitsChg};
        }

        static std::vector<Point> parse(const std::string_view input) {
            return util::getLines(input)
                   | std::views::transform([](const std::string& line) {
                       const auto parts = util::split(line, ",");
                       return Point{std::stoll(parts[0]), std::stoll(parts[1]), std::stoll(parts[2])};
                   })
                   | std::ranges::to<std::vector>();
        }
    };
}
