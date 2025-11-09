#pragma once
#include <functional>
#include <map>
#include <memory>
#include "../util/Solution.h"
using namespace aoc::util;

namespace aoc::year2025 {
    using SolutionCreator = std::function<std::unique_ptr<Solution>()>;
    const std::map<int, SolutionCreator>& solutionMap();
}
