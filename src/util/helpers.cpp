#include <vector>
#include <ranges>
#include <string>

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
    if (lines.size() > 0 && lines.back().empty()) {
        lines.pop_back();
    }

    return lines;
}
