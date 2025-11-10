#pragma once
#include <string>
#include "Solution.h"

namespace aoc::util {
    class InputReader {
    public:
        explicit InputReader(std::string basePath = "") : _basePath(std::move(basePath)) {}
        [[nodiscard]] std::string readInput(int year, int day) const;
        [[nodiscard]] std::string readInputFor(const Solution& solution) const;

    private:
        const std::string _basePath;
    };
}
