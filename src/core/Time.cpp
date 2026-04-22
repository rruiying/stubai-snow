#include "core/Time.hpp"

#include <algorithm>

namespace stubai::core {
    Time::Time() : startTime_(Clock::now()), lastTime_(startTime_) {}

    float Time::tick() {
        ++frameCount_;

        if (fixedTimestep_ > 0.0f) {
            deltaTime_ = fixedTimestep_;
        } else {
            const auto now = Clock::now();
            deltaTime_ = std::chrono::duration<float>(now - lastTime_).count();
            lastTime_ = now;
            deltaTime_ = std::min(deltaTime_, 0.1f);
        }
        totalTime_ += deltaTime_;

        return deltaTime_;
    }

    float Time::fps() const noexcept {
        return (deltaTime_ > 0.0f) ? (1.0f / deltaTime_) : 0.0f;
    }
}