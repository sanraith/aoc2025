#include "InputReader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <fmt/format.h>

#include "Solution.h"

namespace aoc::util {
    static std::string readFileWhole(const std::filesystem::path& path) {
        const std::ifstream in(path, std::ios::in | std::ios::binary);
        if (!in) {
            throw std::runtime_error("Failed to open file: " + path.string());
        }
        std::ostringstream ss;
        ss << in.rdbuf();

        return ss.str();
    }

    std::string InputReader::readInput(const int year, const int day) const {
        const auto path = _config.basePath() / "input" / fmt::format("{}day{:02}.txt", year, day);
        return readFileWhole(path);
    }

    std::string InputReader::readInputFor(const Solution& solution) const {
        return readInput(solution.year(), solution.day());
    }
}
