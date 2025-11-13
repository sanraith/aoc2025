#include "Day01.h"
#include <fmt/core.h>

namespace aoc::year2025 {
    Result Day01::part1(const std::string_view input) {
        // std::cout << "[" << input << "]" << std::endl;
        fmt::print("Input is '{}', length: {}.\n", input, input.length());
        return input.length();
    }

    Result Day01::part2(const std::string_view input) {
        return NotImplementedResult;
    }
}
