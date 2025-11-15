#pragma once
#include <filesystem>
#include <optional>
#include <string>

/** Example config file (aoc2025.config.json)
{
    "eventYear": 2025,
    "copyResultToClipboard": true,
    "sessionCookie": "your_session_cookie_here"
}
*/

namespace aoc ::scaffold {
    class AocConfig {
    public:
        static std::optional<AocConfig> loadFromFile(const std::filesystem::path& configPath);

        [[nodiscard]] int year() const { return _year; }
        [[nodiscard]] const std::string& sessionCookie() const { return _sessionCookie; }
        [[nodiscard]] bool copyResultToClipboard() const { return _copyResultToClipboard; }

    private:
        AocConfig(const int year, const std::string&& sessionCookie, const bool copyResultToClipboard) : _year(year),
            _sessionCookie(std::move(sessionCookie)), _copyResultToClipboard(copyResultToClipboard) {}

        const int _year;
        const std::string _sessionCookie;
        const bool _copyResultToClipboard;
    };
}