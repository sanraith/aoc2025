#include "index.h"
#include <functional>
#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"
#include "Day05.h"
#include "Day06.h"
#include "Day07.h"
#include "Day08.h"
#include "Day09.h"

namespace aoc {
    const std::map<YearMonth, SolutionCreator>& solutionMap() {
        static const std::map<YearMonth, SolutionCreator> solutions{
            {{2025, 1}, [] { return std::make_unique<year2025::Day01>(); }},
            {{2025, 2}, [] { return std::make_unique<year2025::Day02>(); }},
            {{2025, 3}, [] { return std::make_unique<year2025::Day03>(); }},
            {{2025, 4}, [] { return std::make_unique<year2025::Day04>(); }},
            {{2025, 5}, [] { return std::make_unique<year2025::Day05>(); }},
            {{2025, 6}, [] { return std::make_unique<year2025::Day06>(); }},
            {{2025, 7}, [] { return std::make_unique<year2025::Day07>(); }},
            {{2025, 8}, [] { return std::make_unique<year2025::Day08>(); }},
            {{2025, 9}, [] { return std::make_unique<year2025::Day09>(); }},
        };
        return solutions;
    }
}