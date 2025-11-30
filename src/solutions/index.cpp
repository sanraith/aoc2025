#include "index.h"
#include <functional>

namespace aoc {
    const std::map<YearMonth, SolutionCreator>& solutionMap() {
        static const std::map<YearMonth, SolutionCreator> solutions{
        };
        return solutions;
    }
}