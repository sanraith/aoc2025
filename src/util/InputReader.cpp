#include "InputReader.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Solution.h"

namespace aoc::util {
    std::string readFileWhole(const std::string& path) {
        // std::filesystem::path cwd = std::filesystem::current_path();
        // std::cout << "Current directory: " << cwd << '\n';

        const std::ifstream in(path, std::ios::in | std::ios::binary);
        if (!in) {
            throw std::runtime_error("Failed to open file: " + path);
        }
        std::ostringstream ss;
        ss << in.rdbuf();

        return ss.str();
    }

    std::string InputReader::readInput(const int year, const int day) const {
        const std::string path = _basePath + "input/" + std::to_string(year) +
                                 "day" + (day < 10 ? "0" : "") + std::to_string(day) + ".txt";
        return readFileWhole(path);
    }

    std::string InputReader::readInputFor(const Solution& solution) const {
        return readInput(solution.year(), solution.day());
    }
}
