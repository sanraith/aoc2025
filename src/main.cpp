#include <iostream>

#include "solutions/Day01.h"

int main() {
    std::cout << "Hello Advent of Code 2025!" << std::endl;

    auto solution = aoc::year2025::Day01{};
    Context context{"test1234"};
    solution.init(context);

    std::cout << "Solution for 2025-12-01/01: " << solution.part1() << std::endl;
    std::cout << "Solution for 2025-12-01/01: " << solution.part2() << std::endl;

    return 0;
}
