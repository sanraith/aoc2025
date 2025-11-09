#pragma once

#include "Context.h"
#include "Result.h"

namespace aoc::util {
    class Solution {
    public:
        explicit Solution(const std::string_view title) : _title(title) {}
        virtual ~Solution() = default;

        virtual Result part1(std::string_view input) { return NotImplementedResult; }
        virtual Result part2(std::string_view input) { return NotImplementedResult; }

        void init(Context& context) { _context = &context; }

        [[nodiscard]] std::string_view title() const { return _title; }

        [[nodiscard]] Context& context() const {
            if (!_context) { throw std::invalid_argument("Solution is not initialized!"); }
            return *_context;
        }

    private:
        const std::string_view _title;
        Context* _context = nullptr;
    };
}
