#pragma once

#include <string>
#include <vector>
#include <cassert>

namespace aoc::util {
    /** Splits the given text by line. Removes the last empty line if any. */
    std::vector<std::string> getLines(std::string_view text);

    /** Splits the given text by separator. */
    std::vector<std::string> split(std::string_view str, std::string_view separator);

    /** Returns the sign of the given number: -1, 0, 1 */
    template<typename T>
    constexpr T signum(T num) {
        return num < 0 ? -1 : num > 0 ? 1 : 0;
    }

    /** Wraps number x into a range of 0...m-1 (m > 0) */
    template<typename T>
    constexpr T wrap_mod(T num, T range) {
        static_assert(std::is_integral_v<T>, "Integral type required");
        assert(range > 0);
        T wrapped = num % range;
        if (wrapped < 0) wrapped += range;
        return wrapped;
    }
}
