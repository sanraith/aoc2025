#pragma once

#include "Context.h"
#include "Result.h"

namespace aoc::util {
    class Solution {
    public:
        explicit Solution(const std::string_view title) : _title(title), _context(emptyContext()) {}
        virtual ~Solution() = default;

        virtual Result part1(std::string_view input) { return NotImplementedResult; }
        virtual Result part2(std::string_view input) { return NotImplementedResult; }

        // ReSharper disable once CppMemberFunctionMayBeConst
        // ReSharper disable once CppParameterMayBeConstPtrOrRef
        void setContext(Context& context) { _context = context; }
        [[nodiscard]] Context& context() const { return _context; }
        [[nodiscard]] std::string_view title() const { return _title; }

    private:
        const std::string_view _title;
        Context& _context;
    };
}
