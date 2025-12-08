#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <ranges>
#include <iostream>
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
            const auto connectCount = _part1ConnectCount < 0 ? 1000 : _part1ConnectCount;
            const auto points = parse(input);
            std::vector<std::pair<double, std::pair<Point, Point>>> distPointPairs{};
            for (int a = 0; a < points.size(); a++) {
                for (int b = a + 1; b < points.size(); b++) {
                    const auto aPoint = points[a];
                    const auto bPoint = points[b];
                    distPointPairs.push_back({aPoint.euclideanDistance(bPoint), {aPoint, bPoint}});
                }
            }
            std::ranges::sort(distPointPairs);

            using Circuit = std::set<Point>;
            using SharedCircuit = std::shared_ptr<std::set<Point>>;
            std::map<Point, SharedCircuit> circuitsByPoint{};
            int connected = 0;
            //for (const auto [dist,pair] : distPointPairs) {
            for (int i = 0; i < connectCount; i++) {
                context().progress(i, connectCount);
                const auto& [dist, pair] = distPointPairs[i];
                const auto& [a,b] = pair;

                if (circuitsByPoint.contains(a) != circuitsByPoint.contains(b)) {
                    // one is part of a circuit
                    SharedCircuit circuit;
                    if (circuitsByPoint.contains(a)) {
                        circuit = circuitsByPoint[a];
                        circuit->insert(b);
                        circuitsByPoint[b] = circuit;
                    }
                    else {
                        circuit = circuitsByPoint[b];
                        circuit->insert(a);
                        circuitsByPoint[a] = circuit;
                    }
                    connected++;
                }
                else if (!circuitsByPoint.contains(a) && !circuitsByPoint.contains(b)) {
                    // none is part of a circuit
                    const auto circuit = std::make_shared<Circuit>();
                    circuit->insert(a);
                    circuit->insert(b);
                    circuitsByPoint[a] = circuit;
                    circuitsByPoint[b] = circuit;
                    connected++;
                }
                else {
                    // both are part of a circuit
                    auto sourceCircuit = circuitsByPoint[b];
                    const auto targetCircuit = circuitsByPoint[a];
                    if (sourceCircuit == targetCircuit) {
                        continue; // Do nothing if they are in the same circuit
                    }

                    // Merge them to the first one otherwise.
                    for (const auto p : *sourceCircuit) {
                        targetCircuit->insert(p);
                        circuitsByPoint[p] = targetCircuit;
                    }
                    sourceCircuit.reset();
                    connected++;
                }
            }

            std::set<SharedCircuit> circuits;
            for (const auto& val : circuitsByPoint | std::views::values) circuits.insert(val);

            std::vector circuitsVector(circuits.begin(), circuits.end());
            std::ranges::sort(circuitsVector, std::ranges::greater{},
                              [](const SharedCircuit& sc) { return sc->size(); });
            return std::transform_reduce(
                circuitsVector.begin(),
                circuitsVector.begin() + std::min<std::size_t>(3, circuitsVector.size()),
                1ll,
                std::multiplies(),
                [](SharedCircuit const& it) { return static_cast<int64_t>(it->size()); }
            );
        }

        Result part2(const std::string_view input) override {
            const auto points = parse(input);
            std::vector<std::pair<double, std::pair<Point, Point>>> distPointPairs{};
            for (int a = 0; a < points.size(); a++) {
                for (int b = a + 1; b < points.size(); b++) {
                    const auto aPoint = points[a];
                    const auto bPoint = points[b];
                    distPointPairs.push_back({aPoint.euclideanDistance(bPoint), {aPoint, bPoint}});
                }
            }
            std::ranges::sort(distPointPairs);

            using Circuit = std::set<Point>;
            using SharedCircuit = std::shared_ptr<std::set<Point>>;
            std::map<Point, SharedCircuit> circuitsByPoint{};
            int circuitCount = 0;
            std::pair<Point, Point> lastPair{};
            for (int i = 0; i < distPointPairs.size(); i++) {
                context().progress(i, distPointPairs.size());
                const auto& [dist, pair] = distPointPairs[i];
                const auto& [a,b] = pair;
                if (circuitsByPoint.contains(a) != circuitsByPoint.contains(b)) {
                    // one is part of a circuit
                    SharedCircuit circuit;
                    if (circuitsByPoint.contains(a)) {
                        circuit = circuitsByPoint[a];
                        circuit->insert(b);
                        circuitsByPoint[b] = circuit;
                    }
                    else {
                        circuit = circuitsByPoint[b];
                        circuit->insert(a);
                        circuitsByPoint[a] = circuit;
                    }
                }
                else if (!circuitsByPoint.contains(a) && !circuitsByPoint.contains(b)) {
                    // none is part of a circuit
                    const auto circuit = std::make_shared<Circuit>();
                    circuit->insert(a);
                    circuit->insert(b);
                    circuitsByPoint[a] = circuit;
                    circuitsByPoint[b] = circuit;
                    circuitCount++;
                }
                else {
                    // both are part of a circuit
                    auto sourceCircuit = circuitsByPoint[b];
                    const auto targetCircuit = circuitsByPoint[a];
                    if (sourceCircuit == targetCircuit) {
                        continue; // Do nothing if they are in the same circuit
                    }

                    // Merge them to the first one otherwise.
                    for (const auto p : *sourceCircuit) {
                        targetCircuit->insert(p);
                        circuitsByPoint[p] = targetCircuit;
                    }
                    sourceCircuit.reset();
                    circuitCount--;
                }
                if (circuitCount == 1) { lastPair = pair; }
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

            double euclideanDistance(const Point& other) const {
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

        static std::vector<Point> parse(const std::string_view input) {
            const auto lines = util::getLines(input);
            std::vector<Point> points{};
            for (const auto& line : lines) {
                const auto parts = util::split(line, ",");
                points.push_back({std::stoll(parts[0]), std::stoll(parts[1]), std::stoll(parts[2])});
            }
            return points;
        }
    };
}
