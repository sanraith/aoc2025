#include <filesystem>
#include <iostream>
#include <ostream>
#include <fmt/core.h>
#include <chrono>

#include "util/AocCachedWebClient.h"
#include "util/AocConfig.h"
using namespace aoc::util;

struct ScaffoldArgs {
    std::optional<int> year;
    std::optional<int> day;
};

ScaffoldArgs parseArgs(const int argc, char* argv[]) {
    using namespace std::chrono;
    const auto today = floor<days>(system_clock::now());
    const year_month_day ymd{today};

    ScaffoldArgs args{
        .year = static_cast<unsigned>(ymd.month()) == 12 ? static_cast<std::optional<int>>(ymd.year()) : std::nullopt,
        .day = static_cast<unsigned>(ymd.month()) == 12
                   ? static_cast<std::optional<int>>(static_cast<unsigned>(ymd.day()))
                   : std::nullopt
    };

    for (int i = 1; i < argc; ++i) {
        if (const std::string arg = argv[i]; arg == "-d" || arg == "--day") {
            i++;
            if (i < argc) { args.day = std::stoi(argv[i]); }
            else {
                std::cerr << "Error: --day requires an argument." << std::endl;
                exit(1);
            }
        }
        else if (arg == "-y" || arg == "--year") {
            i++;
            if (i < argc) { args.year = std::stoi(argv[i]); }
            else {
                std::cerr << "Error: --day requires an argument." << std::endl;
                exit(1);
            }
        }
        else if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: scaffold -y <year> -d <day> [options]\n"
                "Options:\n"
                "  -d, --day <day>       Specify the day of the puzzle to run.\n"
                "  -y, --year <year>     Specify the year of the puzzle to run.\n"
                "  -h, --help            Show this help message.\n";
            exit(0);
        }
    }

    return args;
}

void load_puzzle_data(const std::filesystem::path& basePath, const AocConfig& config,
                      const int year, const int day) {
    const auto webLoader = AocCachedWebClient(config, basePath);
    const auto input = webLoader.loadPuzzleInput(year, day);
    const auto puzzlePage = webLoader.loadPuzzlePage(year, day);
    if (input) {
        fmt::print("Input loaded, length: {} characters.\n", input->length());
    }
    else {
        fmt::print("Failed to load input.\n");
    }
    if (puzzlePage) {
        fmt::print("Puzzle page loaded, length: {} characters.\n", puzzlePage->length());
    }
    else {
        fmt::print("Failed to load puzzle page.\n");
    }
}

int main(const int argc, char* argv[]) {
    std::cout << "Current path: " << std::filesystem::current_path() << '\n';
    if (const auto configOpt = AocConfig::loadFromDisk()) {
        const auto& config = *configOpt;
        const auto& basePath = config.basePath();

        fmt::print("Year: {}, SessionCookie: \"{}\", CopyResultToClipboard: {}.\n",
                   config.year(),
                   config.sessionCookie().substr(0, 3) + "...",
                   config.copyResultToClipboard() ? "true" : "false"
        );

        const auto [year, day] = parseArgs(argc, argv);

        if (year.has_value() && day.has_value()) {
            using namespace std::chrono;
            const year_month_day todayYmd{floor<days>(system_clock::now())};
            const year_month_day targetYmd{
                std::chrono::year{static_cast<int>(*year)},
                std::chrono::month{12},
                std::chrono::day{static_cast<unsigned>(*day)}
            };
            if (targetYmd <= todayYmd) {
                load_puzzle_data(basePath, config, *year, *day);
            }
            else {
                std::cerr << "Error: Specified date " << *year << "-12-" << *day
                    << " is in the future compared to today "
                    << static_cast<int>(todayYmd.year()) << "-"
                    << static_cast<unsigned>(todayYmd.month()) << "-"
                    << static_cast<unsigned>(todayYmd.day()) << ".\n";
            }
        }
        else {
            std::cerr << "Error: Year and Day must be specified if the current month is not December. See --help.\n";
        }
    }

    return 0;
}
