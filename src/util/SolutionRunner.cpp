#include "SolutionRunner.h"

#include <array>
#include <future>
#include <thread>
#include <fmt/format.h>
#include <algorithm> // for std::max
#include <utility>   // for std::pair

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX   // prevent windows.h from defining min/max macros
#endif
#include <windows.h>
#endif

#if defined(__APPLE__)
#include <cstdio>    // for popen/pclose on mac
#endif

namespace aoc::util {
    struct DurationScale {
        long long scale;
        const char* suffix;
        int maxDecimals;
    };

    static std::string timeStr(const long long nanos) {
        static constexpr std::array<DurationScale, 5> DurationScales{
            {
                {60'000'000'000LL, "m", 2},
                {1'000'000'000LL, "s", 2},
                {1'000'000LL, "ms", 0},
                {1'000LL, "us", 0},
                {1LL, "ns", 0}
            }
        };
        constexpr long long MinDurationScale = DurationScales.back().scale;

        for (const auto& [scale, suffix, maxDecimals] : DurationScales) {
            double scaled = static_cast<double>(nanos) / scale;
            if (scaled >= 1.0 || scale == MinDurationScale) {
                int decimals = std::max(0, maxDecimals - static_cast<int>(std::log10(scaled)));
                return fmt::format("{:.{}f} {}", scaled, decimals, suffix);
            }
        }
        return "0 ns";
    }

    static Result runPart(const std::unique_ptr<Solution>& solution, std::string_view input, const int part) {
        std::atomic<float> asyncProgress{-1};
        const ProgressCallback progressCallback = [&asyncProgress](const float update) {
            asyncProgress.store(update, std::memory_order_relaxed);
        };
        Context context{progressCallback};
        solution->setContext(context);
        const auto partMember = part == 1 ? &Solution::part1 : &Solution::part2;

        const auto start = std::chrono::steady_clock::now();
        auto partFuture = std::async(std::launch::async, [partMember, &solution, &input] {
            const auto startInner = std::chrono::steady_clock::now();
            Result result{NotImplementedResult};
            try {
                result = std::invoke(partMember, *solution, input);
            }
            catch (const std::exception& ex) {
                result = Result{std::format("Unhandled Exception: {}", ex.what()), Result::State::Failure};
            }
            catch (...) {
                result = Result{"Unknown unhandled exception!", Result::State::Failure};
            }
            const auto endInner = std::chrono::steady_clock::now();
            const auto totalElapsedNanos =
                std::chrono::duration_cast<std::chrono::nanoseconds>(endInner - startInner).count();
            return std::pair{result, totalElapsedNanos};
        });

        LineRewriter line{};
        while (partFuture.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
            const auto now = std::chrono::steady_clock::now();
            const auto elapsedNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
            const auto elapsedStr = std::format("{:>8}", std::format("({})", timeStr(elapsedNanos)));
            const auto progressStr = asyncProgress.load(std::memory_order_relaxed) < 0
                                         ? ""
                                         : std::format("{:5.2f}%", asyncProgress * 100.0f);

            line.print(fmt::format("Part {}... {} {}", part, elapsedStr, progressStr));
            std::this_thread::sleep_for(
                std::chrono::milliseconds(SolutionRunner::PROGRESS_UPDATE_DELAY_MS));
        }

        const auto [result, totalElapsedNanos] = partFuture.get();
        const auto totalElapsedStr = std::format("{:>8}", std::format("({})", timeStr(totalElapsedNanos)));

        if (result.state == Result::State::Success) {
            if (result.value.contains('\n')) {
                line.println(fmt::format("Part {} {}:", part, totalElapsedStr));
                line.println(result.value);
            }
            else {
                line.println(fmt::format("Part {} {}: {}", part, totalElapsedStr, result.value));
            }
        }
        else {
            const char* message = (result.state == Result::State::NotImplemented) ? "Not Implemented." : "Failure";
            line.println(fmt::format("Part {} {}: {}", part, totalElapsedStr, message));
            if (result.state != Result::State::NotImplemented) {
                line.println(result.value);
            }
        }

        return result;
    }

#ifdef _WIN32
    // Copy UTF-8 string to the Windows clipboard as UTF-16
    static bool copyToClipboardWindows(const std::string& utf8) {
        if (!OpenClipboard(nullptr)) return false;
        const bool emptyOk = EmptyClipboard();
        (void)emptyOk;

        // Convert UTF-8 to UTF-16 (wchar_t)
        int wideLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), nullptr, 0);
        if (wideLen == 0) {
            CloseClipboard();
            return false;
        }
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (wideLen + 1) * sizeof(wchar_t));
        if (!hMem) {
            CloseClipboard();
            return false;
        }
        void* memPtr = GlobalLock(hMem);
        if (!memPtr) {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
        MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), static_cast<wchar_t*>(memPtr),
                            wideLen);
        static_cast<wchar_t*>(memPtr)[wideLen] = L'\0';
        GlobalUnlock(hMem);
        if (!SetClipboardData(CF_UNICODETEXT, hMem)) {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
        CloseClipboard();
        return true;
    }
#endif

#if defined(__APPLE__)
    static bool copyToClipboardMac(const std::string& utf8) {
        FILE* p = popen("pbcopy", "w");
        if (!p) return false;
        const size_t written = fwrite(utf8.data(), 1, utf8.size(), p);
        const int rc = pclose(p);
        return written == utf8.size() && rc == 0;
    }
#endif

    void SolutionRunner::runParts(const std::unique_ptr<Solution>& solution) const {
        fmt::println("\n--- Day {}: {} ---", solution->day(), solution->title());
        if (const auto inputOpt = _inputReader.loadPuzzleInput(*solution)) {
            const auto& input = *inputOpt;

            Result lastResult{NotImplementedResult};
            if (const auto r1 = runPart(solution, input, 1); r1.state == Result::State::Success) lastResult = r1;
            if (const auto r2 = runPart(solution, input, 2); r2.state == Result::State::Success) lastResult = r2;

            if (lastResult.state == Result::State::Success && _config.copyResultToClipboard()) {
#ifdef _WIN32
                copyToClipboardWindows(lastResult.value);
#elif defined(__APPLE__)
                copyToClipboardMac(lastResult.value);
#else
                fmt::println("(Clipboard copy not implemented on this platform)");
#endif
            }
        }
        else { fmt::println("Unable to load puzzle input!"); }
    }
}
