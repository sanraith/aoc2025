#pragma once

#include "Context.h"
#include "Result.h"

namespace aoc::util {
    class Solution {
    public:
        explicit Solution(const int year, const int day, const std::string_view title)
            : _year(year), _day(day), _title(title), _context(Context::Empty) {}

        virtual ~Solution() = default;

        virtual Result part1(std::string_view input) { return NotImplementedResult; }
        virtual Result part2(std::string_view input) { return NotImplementedResult; }

        // ReSharper disable once CppMemberFunctionMayBeConst
        // ReSharper disable once CppParameterMayBeConstPtrOrRef
        void setContext(Context& context) { _context = context; }
        [[nodiscard]] Context& context() const { return _context; }
        [[nodiscard]] std::string_view title() const { return _title; }
        [[nodiscard]] int year() const { return _year; }
        [[nodiscard]] int day() const { return _day; }

    private:
        const int _year;
        const int _day;
        const std::string_view _title;
        Context& _context;
    };

    template<typename T>
    concept DerivedFromSolution = std::is_base_of_v<Solution, T>;
}
