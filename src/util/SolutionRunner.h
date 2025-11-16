#pragma once

#include "CachedAocDataLoader.h"
#include "AocConfig.h"
#include "Solution.h"

namespace aoc::util {
    class LineRewriter {
    public:
        void print(const std::string& line) {
            std::string padded = line;
            if (line.length() < prevLength) {
                padded += std::string(prevLength - line.length(), ' ');
            }
            std::cout << "\r" << padded << std::flush;
            prevLength = line.length();
        }

        void println(const std::string& line) {
            print(line);
            std::cout << std::endl;
            prevLength = 0;
        }

    private:
        size_t prevLength{0};
    };

    class SolutionRunner {
    public:
        static constexpr int PROGRESS_UPDATE_DELAY_MS = 50;

        explicit SolutionRunner(const AocConfig& config) : _config(config) {}
        void runParts(const std::unique_ptr<Solution>& solution) const;

    private:
        AocConfig _config;
        CachedAocDataLoader _inputReader{_config};
    };
}
