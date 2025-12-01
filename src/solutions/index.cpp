#include "index.h"
#include <functional>
#include "Day01.h"

namespace aoc {
    const std::map<YearMonth, SolutionCreator>& solutionMap() {
        static const std::map<YearMonth, SolutionCreator> solutions{
            {{2025, 1}, [] { return std::make_unique<year2025::Day01>(); }},
        };
        return solutions;
    }
}