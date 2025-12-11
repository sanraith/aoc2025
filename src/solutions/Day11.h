#pragma once
#include "util/Solution.h"
#include "util/helpers.h"
#include <string>
#include <ranges>
#include <vector>
using namespace aoc::util;

namespace aoc::year2025 {
    /** Solution for https://adventofcode.com/2025/day/11 */
    class Day11 final : public Solution {
    public:
        Day11() : Solution(2025, 11, "Reactor") {}

        Result part1(const std::string_view input) override {
            const auto nodes = parse(input);
            return findPaths(NODE_YOU, nodes, /*onlyDacFftPath=*/false);
        }

        Result part2(const std::string_view input) override {
            const auto nodes = parse(input);
            return findPaths(NODE_SVR, nodes, /*onlyDacFftPath=*/true);
        }

    private:
        const std::string NODE_YOU = "you";
        const std::string NODE_OUT = "out";
        const std::string NODE_SVR = "svr";
        const std::string NODE_DAC = "dac";
        const std::string NODE_FFT = "fft";

        using NodeMap = std::map<std::string, std::vector<std::string>>;
        using PathCountCache = std::map<std::pair<int, std::string_view>, int64_t>;

        int64_t findPaths(const std::string& node, const NodeMap& nodes, const bool onlyDacFftPath) const {
            PathCountCache pathCountCache{};
            return findPaths(node, nodes, pathCountCache, onlyDacFftPath, 0);
        }

        int64_t findPaths(const std::string& node, const NodeMap& nodes, PathCountCache& pathCountCache,
                          const bool onlyDacFftPath, int dacFftFlags) const {
            if (node == NODE_DAC) { dacFftFlags |= 1; }
            else if (node == NODE_FFT) { dacFftFlags |= 2; }
            else if (node == NODE_OUT) {
                return !onlyDacFftPath || dacFftFlags == 3 ? 1 : 0;
            }

            auto pathCount = 0ll;
            if (nodes.contains(node)) {
                for (const auto& nextNode : nodes.at(node)) {
                    const std::string_view nextNodeView{nextNode};
                    const auto key = std::pair(dacFftFlags, nextNodeView);
                    if (const auto cachedCount = tryGetValue(key, pathCountCache)) {
                        pathCount += *cachedCount;
                    }
                    else {
                        const auto localCount =
                            findPaths(nextNode, nodes, pathCountCache, onlyDacFftPath, dacFftFlags);
                        pathCountCache[key] = localCount;
                        pathCount += localCount;
                    }
                }
            }

            return pathCount;
        }

        static NodeMap parse(const std::string_view input) {
            return getLines(input) | std::views::transform([](const auto& line) {
                const auto nodeAndOutputs = split(line, ": ");
                const auto node = nodeAndOutputs[0];
                const auto outputs = split(nodeAndOutputs[1], " ");
                return std::pair(node, outputs);
            }) | std::ranges::to<std::map>();
        }
    };
}
