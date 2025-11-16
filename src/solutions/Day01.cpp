#include "Day01.h"

#include <thread>
#include <fmt/core.h>

namespace aoc::year2025 {
    Result Day01::part1(const std::string_view input) {
        // std::cout << "[" << input << "]" << std::endl;
        // fmt::print("Input is '{}', length: {}.\n", input, input.length());
        for (int i = 0; i < 100; i++) {
            context().progress(i, 100);
            std::this_thread::sleep_for(std::chrono::microseconds(20));
        }
        return input.length();
    }

    Result Day01::part2(const std::string_view input) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        // throw std::logic_error("IDK");
        return NotImplementedResult;
    }
}
