#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <utility>

namespace aoc::util {
    class AocConfig {
    public:
        static const std::string_view CONFIG_FILE_NAME;
        static std::optional<AocConfig> loadFromDisk();
        static std::optional<AocConfig> loadFromPath(const std::filesystem::path& basePath);
        static std::optional<std::filesystem::path> findBasePath(
            const std::optional<std::filesystem::path>& start = std::nullopt);

        [[nodiscard]] const std::filesystem::path& basePath() const { return _basePath; }
        [[nodiscard]] const std::filesystem::path& configFilePath() const { return _configFilePath; }
        [[nodiscard]] int year() const { return _year; }
        [[nodiscard]] const std::string& sessionCookie() const { return _sessionCookie; }
        [[nodiscard]] bool copyResultToClipboard() const { return _copyResultToClipboard; }

    private:
        AocConfig(const std::filesystem::path& basePath, const int year, std::string sessionCookie,
                  const bool copyResultToClipboard) :
            _basePath(basePath), _configFilePath(basePath / CONFIG_FILE_NAME),
            _year(year),
            _sessionCookie(std::move(sessionCookie)),
            _copyResultToClipboard(copyResultToClipboard) {}

        const std::filesystem::path _basePath;
        const std::filesystem::path _configFilePath;
        const int _year;
        const std::string _sessionCookie;
        const bool _copyResultToClipboard;
    };

    inline const std::string_view AocConfig::CONFIG_FILE_NAME = "aoc2025.config.json";
}

/** Example config file (aoc2025.config.json)
{
    "eventYear": 2025,
    "copyResultToClipboard": true,
    "sessionCookie": "your_session_cookie_here"
}
*/
