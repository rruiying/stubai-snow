#ifndef STUBAI_CORE_TIME_HPP
#define STUBAI_CORE_TIME_HPP

#include <chrono>
#include <cstdint>

namespace stubai::core {

    class Time {
        public:
            Time();

            float tick();

            void setFixedTimestep(float dt) noexcept { fixedTimestep_ = dt; }
            void clearFixedTimestep() noexcept { fixedTimestep_ = 0.0f; }

            [[nodiscard]]float deltaTime() const noexcept { return deltaTime_; }
            [[nodiscard]]float totalTime() const noexcept { return totalTime_; }
            [[nodiscard]]std::uint64_t frameCount() const noexcept { return frameCount_; }
            [[nodiscard]]float fps() const noexcept;

        private:
            using Clock = std::chrono::steady_clock;
            Clock::time_point startTime_;
            Clock::time_point lastTime_;
            float fixedTimestep_ = 0.0f;
            float deltaTime_ = 0.0f;
            float totalTime_ = 0.0f;
            std::uint64_t frameCount_ = 0;
    };
} // namespace stubai::core

#endif // STUBAI_CORE_TIME_HPP