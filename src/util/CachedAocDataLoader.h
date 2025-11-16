#pragma once

#include <filesystem>
#include <string>

#include "AocConfig.h"
#include "util/Solution.h"

namespace aoc::util {
    class CachedAocDataLoader {
    public:
        explicit CachedAocDataLoader(const AocConfig& config) // NOLINT(*-pass-by-value)
            : _config(config),
              _cachePath(config.basePath() / ".cache"),
              _inputPath(config.basePath() / "input") {}

        [[nodiscard]] std::optional<std::string> loadPuzzlePage(int year, int day) const;
        [[nodiscard]] std::optional<std::string> loadPuzzleInput(int year, int day) const;

        template<DerivedFromSolution T>
        [[nodiscard]] std::optional<std::string> loadPuzzleInput(const T& solution) const {
            return loadPuzzleInput(solution.year(), solution.day());
        }

    private:
        const AocConfig _config;
        const std::filesystem::path _cachePath;
        const std::filesystem::path _inputPath;
    };
}
