#include "AocConfig.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std::string_literals;

namespace aoc::util {
    void createEmptyConfigFile(const std::filesystem::path& configPath) {
        json configJson;
        configJson["eventYear"] = 2025;
        configJson["sessionCookie"] = "";
        configJson["copyResultToClipboard"] = false;

        std::ofstream file(configPath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Could not open file to write!" << std::endl;
            return;
        }

        file << configJson.dump(4);
    }

    std::optional<AocConfig> AocConfig::loadFromPath(const std::filesystem::path& basePath) {
        const auto configPath = basePath / CONFIG_FILE_NAME;
        if (!std::filesystem::exists(configPath)) {
            std::cerr << "Config file does not exist at path: "s +
                (std::filesystem::current_path() / configPath).string() << std::endl;
            createEmptyConfigFile(configPath);
            std::cerr <<
                "An empty config file has been created at the specified path. Please fill it out and rerun the program."
                << std::endl;
            return std::nullopt;
        }

        std::ifstream file(configPath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Could not open file!" << std::endl;
            return std::nullopt;
        }

        try {
            json configJson = json::parse(file);
            const int year = configJson["eventYear"];
            const std::string sessionCookie = configJson["sessionCookie"];
            const bool copyResultToClipboard = configJson.value("copyResultToClipboard", false);

            return AocConfig{basePath, year, sessionCookie, copyResultToClipboard};
        }
        catch (json::parse_error& e) {
            std::cerr << "Failed to parse config file: "s + e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<std::filesystem::path>
    AocConfig::findBasePath(const std::optional<std::filesystem::path>& startOpt) {
        auto path = std::filesystem::absolute(startOpt ? *startOpt : std::filesystem::current_path());
        bool found{};
        while (!((found = std::filesystem::exists(path / CONFIG_FILE_NAME))) && path.has_parent_path()) {
            path = path.parent_path();
        }

        return found ? std::optional{path} : std::nullopt;
    }

    std::optional<AocConfig> AocConfig::loadFromDisk() {
        const auto basePathOpt = findBasePath();
        return basePathOpt ? loadFromPath(*basePathOpt) : std::nullopt;
    }
}
