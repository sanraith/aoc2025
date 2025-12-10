#pragma once
#include <algorithm>
#include <functional>
#include <string>

namespace aoc::util {
    using ProgressCallback = std::function<void(float)>;
    using StatusCallback = std::function<void(std::string)>;

    class Context {
    public:
        static Context Empty;
        explicit Context() = default;

        explicit Context(ProgressCallback progressCallback, StatusCallback statusCallback)
            : _progressCallback(std::move(progressCallback)), _statusCallback(std::move(statusCallback)) {}

        void progress(float progressValue) const {
            if (_progressCallback.has_value()) {
                progressValue = std::clamp(progressValue, 0.0f, 1.0f);
                _progressCallback.value()(progressValue);
            }
        }

        void progress(auto current, auto max) const {
            const auto divisor{static_cast<float>(max)};
            if (divisor == 0.0f) { progress(1.0f); }
            else { progress(static_cast<float>(current) / divisor); }
        }

        void statusMsg(std::string&& msg) const {
            if (_statusCallback.has_value()) { _statusCallback.value()(std::move(msg)); }
        }

    private:
        std::optional<ProgressCallback> _progressCallback{};
        std::optional<StatusCallback> _statusCallback{};
    };

    inline Context Context::Empty{};
}
