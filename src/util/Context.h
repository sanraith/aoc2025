#pragma once
#include <algorithm>
#include <functional>

namespace aoc::util {
    using ProgressCallback = std::function<void(float)>;

    class Context {
    public:
        static Context Empty;
        explicit Context() = default;
        explicit Context(ProgressCallback progressCallback) : _progressCallback(std::move(progressCallback)) {}

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

    private:
        std::optional<ProgressCallback> _progressCallback{};
    };

    inline Context Context::Empty{};
}
