#include "index.h"
#include <functional>
#include <memory>
#include "Day01.h"

namespace aoc::year2025 {
    const std::map<int, SolutionCreator>& solutionMap() {
        static const std::map<int, SolutionCreator> solutions{
            {1, [] { return std::make_unique<Day01>(); }},
        };
        return solutions;
    }
}
