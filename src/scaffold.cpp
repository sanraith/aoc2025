#include <filesystem>
#include <iostream>
#include <ostream>
#include <fmt/core.h>

#include "scaffold/AocCachedWebClient.h"
#include "scaffold/AocConfig.h"


using namespace aoc::scaffold;

int main() {
    std::cout << "Current path: " << std::filesystem::current_path() << '\n';
    const std::filesystem::path basePath{".."};
    const auto configPath = basePath / "aoc2025.config.json";
    if (const auto configOpt = AocConfig::loadFromFile(configPath)) {
        const auto& config = *configOpt;
        fmt::print("Year: {}, SessionCookie: \"{}\", CopyResultToClipboard: {}\n",
                   config.year(),
                   config.sessionCookie().substr(0, 3) + "...",
                   config.copyResultToClipboard() ? "true" : "false"
        );

        const auto webLoader = AocCachedWebClient(config, basePath);
        const auto input = webLoader.loadPuzzleInput(2024, 1);
        const auto puzzlePage = webLoader.loadPuzzlePage(2024, 1);
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

    return 0;
}
