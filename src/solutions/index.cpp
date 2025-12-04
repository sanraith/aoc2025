#include "index.h"
#include <functional>
#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"

namespace aoc {
    const std::map<YearMonth, SolutionCreator>& solutionMap() {
        static const std::map<YearMonth, SolutionCreator> solutions{
            {{2025, 1}, [] { return std::make_unique<year2025::Day01>(); }},
            {{2025, 2}, [] { return std::make_unique<year2025::Day02>(); }},
            {{2025, 3}, [] { return std::make_unique<year2025::Day03>(); }},
            {{2025, 4}, [] { return std::make_unique<year2025::Day04>(); }},
        };
        return solutions;
    }
}