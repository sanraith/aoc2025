#include <filesystem>
#include <iostream>
#include <ostream>

#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_ios.h"
#include "curlcpp/curl_exception.h"
#include <fmt/core.h>

#include "scaffold/AocConfig.h"

using std::cout;
using std::endl;
using std::ostringstream;
using curl::curl_easy;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using namespace std::string_literals;

namespace aoc::scaffold {
    void saveInputToFile(int year, int day, const std::string_view sessionCookie) {
        // Create input fileStream to save response to
        const std::filesystem::path inputPath{"input"};
        std::ofstream inputFileStream;
        inputFileStream.open(inputPath / fmt::format("{}day{:02}.txt", year, day));

        // Create a curl_ios object to handle the stream
        curl_ios<std::ostream> responseWriter(inputFileStream);

        // Pass the writer to the easy constructor and watch the content returned in that variable!
        curl_easy easy(responseWriter);

        const auto curlAocUrl = fmt::format("https://adventofcode.com/{}/day/{}/input", year, day);
        // Add some option to the easy handle
        easy.add<CURLOPT_URL>(curlAocUrl.c_str());
        easy.add<CURLOPT_FOLLOWLOCATION>(1L);
        easy.add<CURLOPT_USERAGENT>("https://github.com/sanraith/aoc2025 by sanraith@users.noreply.github.com");
        const auto curlSessionCookie = fmt::format("session={}", sessionCookie);
        easy.add<CURLOPT_COOKIE>(curlSessionCookie.c_str());

        try {
            easy.perform();
        } catch (curl_easy_exception& error) {
            // If you want to print the last error.
            std::cerr << error.what() << std::endl;

            // If you want to print the entire error stack you can do
            curl_easy_exception::print_traceback();
        }
    }
}

using namespace aoc::scaffold;

int main() {
    std::cout << "Current path: "
            << std::filesystem::current_path() << '\n';
    const auto configPath = std::filesystem::path{".."} / "aoc2025.config.json";
    if (const auto configOpt = AocConfig::loadFromFile(configPath)) {
        const auto config = *configOpt;
        fmt::print("Year: {}, Session Cookie: {}, CopyResultToClipboard: {}.\n",
                   config.year(),
                   config.sessionCookie(),
                   config.copyResultToClipboard() ? "true" : "false"
        );
    }

    return 0;
}