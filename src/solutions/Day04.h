#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <map>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/4 */
    class Day04 final : public Solution {
    public:
        Day04() : Solution(2025, 4, "Printing Department") {}

        Result part1(const std::string_view input) override {
            auto grid = parse(input);
            auto& tiles = grid.tiles;
            int canAccessCount = 0;

            for (int y = 0; y < grid.height; y++) {
                for (int x = 0; x < grid.width; x++) {
                    const auto pos = Point{x, y};
                    if (tiles[pos] != TILE_ROLL) { continue; }
                    if (countNeighbours(pos, tiles) < 4) { canAccessCount++; }
                }
            }

            return canAccessCount;
        }

        Result part2(const std::string_view input) override {
            auto grid = parse(input);
            auto& tiles = grid.tiles;
            int canAccessCount = 0;

            bool canAccessNewRolls = true;
            while (canAccessNewRolls) {
                canAccessNewRolls = false;
                auto tilesNext = tiles;
                for (int y = 0; y < grid.height; y++) {
                    for (int x = 0; x < grid.width; x++) {
                        const auto pos = Point{x, y};
                        if (tiles[pos] != TILE_ROLL) { continue; }
                        if (countNeighbours(pos, tiles) < 4) {
                            canAccessNewRolls = true;
                            canAccessCount++;
                            tilesNext[pos] = TILE_EMPTY;
                        }
                    }
                }
                tiles = tilesNext;
            }

            return canAccessCount;
        }

    private:
        using Tile = char;
        const Tile TILE_ROLL = '@';
        const Tile TILE_EMPTY = '.';

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
        };

        struct Grid {
            int width{};
            int height{};
            std::map<Point, Tile> tiles{};
        };

        const std::vector<Point> _directions = {
            Point{0, -1}, Point{1, -1}, Point{1, 0}, Point{1, 1},
            Point{0, 1}, Point{-1, 1}, Point{-1, 0}, Point{-1, -1}
        };

        [[nodiscard]] int countNeighbours(const Point pos, const std::map<Point, Tile>& tiles) const {
            int neighbourCount = 0;
            for (const auto& dir : _directions) {
                const auto neighbor = pos + dir;
                if (!tiles.contains(neighbor)) { continue; }
                neighbourCount += tiles.at(neighbor) == TILE_ROLL ? 1 : 0;
                if (neighbourCount >= 4) { break; }
            }
            return neighbourCount;
        }

        static void print(const Grid& grid) {
            for (int y = 0; y < grid.height; y++) {
                for (int x = 0; x < grid.width; x++) {
                    std::cout << grid.tiles.at({x, y});
                }
                std::cout << '\n';
            }
        }

        static Grid parse(const std::string_view input) {
            const auto lines = util::getLines(input);
            std::map<Point, Tile> tiles{};
            for (int y = 0; y < lines.size(); y++) {
                const auto& line = lines[y];
                for (int x = 0; x < line.size(); x++) {
                    const auto tile = line[x];
                    tiles[{x, y}] = tile;
                }
            }
            return Grid{
                .width = static_cast<int>(lines[0].size()),
                .height = static_cast<int>(lines.size()),
                .tiles = std::move(tiles)
            };
        }
    };
}
