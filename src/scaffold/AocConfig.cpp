#include "AocConfig.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std::string_literals;

namespace aoc::scaffold {
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

    std::optional<AocConfig> AocConfig::loadFromFile(const std::filesystem::path& configPath) {
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

            return AocConfig{year, std::move(sessionCookie), copyResultToClipboard};
        } catch (json::parse_error& e) {
            std::cerr << "Failed to parse config file: "s + e.what() << std::endl;
            return std::nullopt;
        }
    }
}
