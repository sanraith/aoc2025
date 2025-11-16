#pragma once
#include <filesystem>
#include <string>

#include "AocConfig.h"
#include "Solution.h"

namespace aoc::util {
    class InputReader {
    public:
        explicit InputReader(const AocConfig& config) : _config(config) {}
        [[nodiscard]] std::string readInput(int year, int day) const;
        [[nodiscard]] std::string readInputFor(const Solution& solution) const;

    private:
        const AocConfig _config;
    };
}
