#pragma once
#include <string>
#include <utility>

namespace aoc::util {
    class Context {
    public:
        explicit Context(std::string input) : _input(std::move(input)) {}

        void progress(float progress);
        const std::string& input() { return _input; }

    private:
        std::string _input;
    };
}
