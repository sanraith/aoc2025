#include <iostream>
#include <ranges>

#include "solutions/index.h"
#include "util/SolutionRunner.h"

void runDay(const int year, const int day) {
    if (!aoc::solutionMap().contains({year, day})) {
        std::cout << "Selected day (" << year << "-12-" << day << ") is not implemented yet!" << std::endl;
        return;
    }

    const std::unique_ptr<Solution> solution = aoc::solutionMap().at({year, day})();
    const SolutionRunner runner{*AocConfig::loadFromDisk()}; // TODO extract
    runner.runParts(solution);
}

void runAllDays() {
    std::cout << "Running all days..." << std::endl;
    for (const auto [year, day] : aoc::solutionMap() | std::views::keys
    ) {
        runDay(year, day);
    }
}

void runLastDay() {
    const auto [lastYear, lastDay]{aoc::solutionMap().rbegin()->first};
    std::cout << "Running last day..." << std::endl;
    runDay(lastYear, lastDay);
}

void parseArgs(const int argc, char* argv[]) {
    std::optional<int> year{};
    std::optional<int> day{};
    for (int i = 1; i < argc; ++i) {
        if (const std::string arg = argv[i]; arg == "-d" || arg == "--day") {
            i++;
            if (i < argc) {
                const std::string dayStr = argv[i];
                day = std::stoi(dayStr);
                std::cout << "Selected day: " << *day << std::endl;
            }
            else {
                std::cerr << "Error: --day requires an argument." << std::endl;
                exit(1);
            }
        }
        else if (arg == "-y" || arg == "--year") {
            i++;
            if (i < argc) { year = std::stoi(argv[i]); }
            else {
                std::cerr << "Error: --day requires an argument." << std::endl;
                exit(1);
            }
        }
        else if (arg == "-l" || arg == "--last") {
            runLastDay();
            break;
        }
        else if (arg == "-a" || arg == "--all") {
            runAllDays();
            break;
        }
        else if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: aoc2025 [options]\n"
                << "Options:\n"
                << "  --help, -h       Show this help message\n"
                << "  --year, -y <n>   Select year n to run\n"
                << "  --day, -d <n>    Select day n to run\n"
                << "  --last, -l       Select the last available day\n"
                << "  --all, -a        Run all available days\n";
            break;
        }
    }

    if (year.has_value() && day.has_value()) {
        runDay(*year, *day);
    }
    else if (argc == 1) {
        // no user args provided
        runAllDays();
    }

    std::cout << std::endl;
    exit(0);
}

int main(const int argc, char* argv[]) {
    std::cout << "--- Advent of Code 2025 ---" << std::endl;
    parseArgs(argc, argv);
    return 0;
}
