#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/7 */
    class Day07 final : public Solution {
    public:
        Day07() : Solution(2025, 7, "Laboratories") {}

        Result part1(const std::string_view input) override {
            auto grid = parse(input);
            std::queue<Point> queue{};
            queue.push(grid.start + down);

            int count = 0;
            int currentHeight = -1;
            while (!queue.empty()) {
                const auto current = queue.front();
                queue.pop();
                if (current.y > grid.height) {
                    continue;
                }

                if (current.y > currentHeight) {
                    currentHeight = current.y;
                    // print(grid);
                }

                if (grid.tiles.contains(current)) {
                    const auto existingTile = grid.tiles[current];
                    if (existingTile == TILE_BEAM) {
                        continue;
                    }
                    count += 1;
                    queue.push(current + left);
                    queue.push(current + right);
                }
                else {
                    grid.tiles[current] = TILE_BEAM;
                    queue.push(current + down);
                }
            }

            // print(grid);

            return count;
        }

        Result part2(const std::string_view input) override {
            auto grid = parse(input);
            std::map<Point, int64_t> cache{};
            const auto count = countPaths(grid.start, grid, cache);

            return count;
        }

    private:
        using Tile = char;
        static constexpr Tile TILE_BEAM_START = 'S';
        static constexpr Tile TILE_BEAM = '|';
        static constexpr Tile TILE_SPLITTER = '^';
        static constexpr Tile TILE_SPACE = '.';

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

        const Point down{0, 1};
        const Point left{-1, 0};
        const Point right{1, 0};

        struct Grid {
            int width{};
            int height{};
            Point start{};
            std::map<Point, Tile> tiles{};
        };

        int64_t countPaths(const Point start, Grid& grid, std::map<Point, int64_t>& cache) {
            if (cache.contains(start)) {
                return cache[start];
            }

            std::queue<Point> queue{};
            queue.push(start);
            auto count = 0ll;
            while (!queue.empty()) {
                const auto current = queue.front();
                queue.pop();
                if (current.y > grid.height) {
                    count += 1;
                    continue;
                }

                if (grid.tiles.contains(current) && grid.tiles[current] == TILE_SPLITTER) {
                    count += countPaths(current + left, grid, cache);
                    count += countPaths(current + right, grid, cache);
                }
                else {
                    grid.tiles[current] = TILE_BEAM;
                    queue.push(current + down);
                }
            }
            cache[start] = count;

            return count;
        }

        static void print(Grid& grid) {
            for (int y = 0; y < grid.height; y++) {
                for (int x = 0; x < grid.width; x++) {
                    Tile tile = '.';
                    if (grid.tiles.contains({x, y})) {
                        tile = grid.tiles[{x, y}];
                    }
                    std::cout << tile;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        static Grid parse(const std::string_view input) {
            const auto lines = util::getLines(input);
            std::map<Point, Tile> tiles{};
            Point start{};
            for (int y = 0; y < lines.size(); y++) {
                const auto& line = lines[y];
                for (int x = 0; x < line.size(); x++) {
                    const auto tile = line[x];
                    if (tile != TILE_SPACE) { tiles[{x, y}] = tile; }
                    if (tile == TILE_BEAM_START) { start = {x, y}; }
                }
            }

            return Grid{static_cast<int>(lines[0].size()), static_cast<int>(lines.size()), start, std::move(tiles)};
        }
    };
}
