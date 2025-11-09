#include <iostream>

#include "solutions/Day01.h"
#include "solutions/SolutionIndex.h"

int main() {
    std::cout << "Hello Advent of Code 2025!" << std::endl;

    const std::string input{"test1234"};
    const std::unique_ptr<Solution> solution = aoc::year2025::solutionMap().at(1)();
    Context context{input};
    solution->init(context);

    std::cout << "Solution for 2025-12-01/01: " << solution->part1(input) << std::endl;
    std::cout << "Solution for 2025-12-01/01: " << solution->part2(input) << std::endl;

    return 0;
}
