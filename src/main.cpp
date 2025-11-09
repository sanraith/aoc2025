#include <iostream>
#include <ranges>

#include "solutions/index.h"

void runDay(const int day) {
    if (!aoc::year2025::solutionMap().contains(day)) {
        std::cout << "Selected day (" << day << ") is not implemented yet!" << std::endl;
        return;
    }

    const std::string input{"test1234"};
    const std::unique_ptr<Solution> solution = aoc::year2025::solutionMap().at(day)();
    Context context{input};
    solution->init(context);

    std::cout << "\n--- Day " << day << ": " << solution->title() << " ---" << std::endl;
    std::cout << "Part 1: " << solution->part1(input) << std::endl;
    std::cout << "Part 2: " << solution->part2(input) << std::endl;
}

void runAllDays() {
    std::cout << "Running all days..." << std::endl;
    for (const int day : aoc::year2025::solutionMap() | std::views::keys) {
        runDay(day);
    }
}

void runLastDay() {
    const int lastDay{aoc::year2025::solutionMap().rbegin()->first};
    std::cout << "Running last day..." << lastDay << std::endl;
    runDay(lastDay);
}

void parseArgs(const int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (const std::string arg = argv[i]; arg == "-d" || arg == "--day") {
            i++;
            if (i < argc) {
                const std::string dayStr = argv[i];
                const int day = std::stoi(dayStr);
                std::cout << "Selected day: " << day << std::endl;
                runDay(day);
                exit(0);
            }
            else {
                std::cerr << "Error: --day requires an argument." << std::endl;
                exit(1);
            }
        }
        else if (arg == "-l" || arg == "--last") {
            runLastDay();
            exit(0);
        }
        else if (arg == "-a" || arg == "--all") {
            runAllDays();
            exit(0);
        }
        else if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: aoc2025 [options]\n"
                << "Options:\n"
                << "  --help, -h       Show this help message\n"
                << "  --day, -d <n>    Select day n to run\n"
                << "  --last, -l       Select the last available day\n"
                << "  --all, -a        Run all available days\n";

            exit(0);
        }
    }

    if (argc == 1) {
        // no user args provided
        runAllDays();
    }
}

int main(const int argc, char* argv[]) {
    std::cout << "--- Advent of Code 2025 ---" << std::endl;
    parseArgs(argc, argv);
    return 0;
}
