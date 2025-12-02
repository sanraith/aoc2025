#include <vector>
#include <ranges>
#include <string>

namespace aoc::util {
    std::vector<std::string> getLines(std::string_view text) {
        namespace rv = std::ranges::views;
        auto view = text
                    | rv::split('\n')
                    | rv::transform([](auto subStr) {
                        std::string s{std::ranges::begin(subStr), std::ranges::end(subStr)};
                        if (!s.empty() && s.back() == '\r') s.pop_back();
                        return s;
                    });

        std::vector lines(view.begin(), view.end());
        if (!lines.empty() && lines.back().empty()) {
            lines.pop_back();
        }

        return lines;
    }

    std::vector<std::string> split(std::string_view str, std::string_view separator) {
        std::vector<std::string> result{};
        for (auto&& subrange : std::views::split(str, separator)) {
            result.emplace_back(subrange.begin(), subrange.end());
        }
        return result;
    }
}
