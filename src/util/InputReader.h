#pragma once
#include <string>

namespace aoc::util {
    class InputReader {
    public:
        explicit InputReader(std::string basePath = "") : _basePath(std::move(basePath)) {}
        [[nodiscard]] std::string readInput(int year, int day) const;

    private:
        const std::string _basePath;
    };
}
