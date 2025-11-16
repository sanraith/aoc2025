#include "AocCachedWebClient.h"

#include <fstream>
#include <sstream>
#include <string>
#include <fmt/format.h>
#include <filesystem>
#include <iostream>
#include <ostream>

#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_ios.h"
#include "curlcpp/curl_exception.h"
namespace fs = std::filesystem;

namespace aoc::scaffold {
    void saveUrlToFile(const std::string_view curlAocUrl,
                       const fs::path& targetFilePath,
                       const std::string_view sessionCookie) {
        // Create input fileStream to save response to
        std::ofstream inputFileStream;
        inputFileStream.open(targetFilePath);

        // Create a curl_ios object to handle the stream
        curl::curl_ios<std::ostream> responseWriter(inputFileStream);

        // Pass the writer to the easy constructor and watch the content returned in that variable!
        curl::curl_easy easy(responseWriter);

        // Add some option to the easy handle
        easy.add<CURLOPT_URL>(curlAocUrl.data());
        easy.add<CURLOPT_FOLLOWLOCATION>(1L);
        easy.add<CURLOPT_USERAGENT>("https://github.com/sanraith/aoc2025 by sanraith@users.noreply.github.com");
        const auto curlSessionCookie = fmt::format("session={}", sessionCookie);
        easy.add<CURLOPT_COOKIE>(curlSessionCookie.c_str());

        try {
            easy.perform();
        }
        catch (curl::curl_easy_exception& error) {
            // If you want to print the last error.
            std::cerr << error.what() << std::endl;

            // If you want to print the entire error stack you can do
            curl::curl_easy_exception::print_traceback();
        }
    }

    static std::string readFileWhole(const fs::path& path) {
        const std::ifstream in(path, std::ios::in | std::ios::binary);
        if (!in) {
            throw std::runtime_error("Failed to open file: " + path.string());
        }
        std::ostringstream ss;
        ss << in.rdbuf();

        return ss.str();
    }

    std::optional<std::string> AocCachedWebClient::loadPuzzleInput(const int year, const int day) const {
        const auto cachedInputFilePath = _cachePath / fmt::format("{}day{:02}_input.txt", year, day);
        const auto inputFilePath = _inputPath / fmt::format("{}day{:02}.txt", year, day);

        try {
            if (!fs::exists(inputFilePath)) {
                std::cout << "Local input file not found, loading from .cache: " << cachedInputFilePath << '\n';
                if (!fs::exists(cachedInputFilePath)) {
                    const auto curlAocUrl = fmt::format("https://adventofcode.com/{}/day/{}/input", year, day);
                    std::cout << "Cached input file not found, downloading from: " << curlAocUrl << std::endl;
                    saveUrlToFile(curlAocUrl, cachedInputFilePath, _config.sessionCookie());
                }
                fs::copy_file(cachedInputFilePath, inputFilePath);
            }
            return readFileWhole(inputFilePath);
        }
        catch (const std::exception& ex) {
            std::cerr << "Error reading puzzle input for " << year << " day " << day << ": " << ex.what() << '\n';
            return std::nullopt;
        }
    }

    std::optional<std::string> AocCachedWebClient::loadPuzzleInput(const util::Solution& solution) const {
        return loadPuzzleInput(solution.year(), solution.day());
    }

    std::optional<std::string> AocCachedWebClient::loadPuzzlePage(int year, int day) const {
        const auto cachedPuzzleFilePath = _cachePath / fmt::format("{}day{:02}_puzzle.txt", year, day);
        try {
            if (!fs::exists(cachedPuzzleFilePath)) {
                const auto curlAocUrl = fmt::format("https://adventofcode.com/{}/day/{}", year, day);
                std::cout << "Cached puzzle page not found, downloading from: " << curlAocUrl << std::endl;
                saveUrlToFile(curlAocUrl, cachedPuzzleFilePath, _config.sessionCookie());
            }
            return readFileWhole(cachedPuzzleFilePath);
        }
        catch (const std::exception& ex) {
            std::cerr << "Error reading puzzle input for " << year << " day " << day << ": " << ex.what() << '\n';
            return std::nullopt;
        }
    }
}
