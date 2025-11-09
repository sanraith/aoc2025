#pragma once
#include <algorithm>
#include <functional>

namespace aoc::util {
    using ProgressCallback = std::function<void(float)>;

    class Context {
    public:
        void progress(float progressValue) const {
            progressValue = std::clamp(progressValue, 0.0f, 1.0f);
            if (_progressCallback.has_value()) {
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

    inline Context& emptyContext() {
        static Context emptyContext{};
        return emptyContext;
    }
}
