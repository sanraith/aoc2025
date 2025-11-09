#pragma once

#include "Context.h"
#include "Result.h"

namespace aoc::util {
    class Solution {
    public:
        Solution() = default;
        virtual ~Solution() = default;

        virtual Result part1() { return NotImplementedResult; }
        virtual Result part2() { return NotImplementedResult; }

        void init(Context& context) { _context = &context; }

        [[nodiscard]] Context& context() const {
            if (!_context) { throw std::invalid_argument("Solution is not initialized"); }
            return *_context;
        }

    private:
        Context* _context = nullptr;
    };
}
