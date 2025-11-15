#pragma once

#include <filesystem>
#include <string>

#include "AocConfig.h"

namespace aoc ::scaffold {
    class AocCachedWebClient {
    public:
        explicit AocCachedWebClient(const AocConfig& config, const std::filesystem::path& basePath) // NOLINT(*-pass-by-value)
            : _config(config),
              _basePath(basePath),
              _cachePath(basePath / ".cache"),
              _inputPath(basePath / "input") {}

        [[nodiscard]] std::optional<std::string> loadPuzzleInput(int year, int day) const;
        [[nodiscard]] std::optional<std::string> loadPuzzlePage(int year, int day) const;

    private:
        const AocConfig _config;
        const std::filesystem::path _basePath;
        const std::filesystem::path _cachePath;
        const std::filesystem::path _inputPath;
    };
}
