#pragma once
#include <functional>
#include <map>
#include <memory>
#include "../util/Solution.h"
using namespace aoc::util;

namespace aoc {
    using SolutionCreator = std::function<std::unique_ptr<Solution>()>;

    struct YearMonth {
        int year;
        int month;

        bool operator<(const YearMonth& other) const {
            return std::tie(year, month) < std::tie(other.year, other.month);
        }
    };

    const std::map<YearMonth, SolutionCreator>& solutionMap();
}