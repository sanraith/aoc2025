#include "SolutionRunner.h"

#include <array>
#include <future>
#include <thread>
#include <fmt/format.h>

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
                {1'000'000'000LL, "s", 3},
                {1'000'000LL, "ms", 0},
                {1'000LL, "μs", 0},
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

    static void runPart(const std::unique_ptr<Solution>& solution, std::string_view input, const int part) {
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
            return std::pair(result, totalElapsedNanos);
        });

        LineRewriter line{};
        while (partFuture.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
            const auto now = std::chrono::steady_clock::now();
            const auto elapsedNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
            const auto elapsedStr = std::format("{:>9}", std::format("({})", timeStr(elapsedNanos)));
            const auto progressStr = asyncProgress.load(std::memory_order_relaxed) < 0
                                         ? ""
                                         : std::format("{:5.2f}%", asyncProgress * 100.0f);

            line.print(fmt::format("Part {}... {} {}", part, elapsedStr, progressStr));
            std::this_thread::sleep_for(
                std::chrono::milliseconds(SolutionRunner::PROGRESS_UPDATE_DELAY_MS));
        }

        const auto [result,totalElapsedNanos] = partFuture.get();
        const auto totalElapsedStr = std::format("{:>9}", std::format("({})", timeStr(totalElapsedNanos)));

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
    }

    void SolutionRunner::runParts(const std::unique_ptr<Solution>& solution) const {
        fmt::println("\n--- Day {}: {} ---", solution->day(), solution->title());
        if (const auto inputOpt = _inputReader.loadPuzzleInput(*solution)) {
            const auto input = *inputOpt;
            runPart(solution, input, 1);
            runPart(solution, input, 2);
        }
        else { fmt::println("Unable to load puzzle input!"); }
    }
}
