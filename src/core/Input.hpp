#ifndef STUBAI_CORE_INPUT_HPP
#define STUBAI_CORE_INPUT_HPP

#include <array>

struct GLFWwindow;

namespace stubai::core {

    class Input {
        public:
            static constexpr int kKeyCount = 512;

            explicit Input(GLFWwindow* window);

            void update();

            [[nodiscard]] bool isKeyDown(int key) const noexcept;
            [[nodiscard]] bool wasKeyPressed(int key) const noexcept;
            [[nodiscard]] bool wasKeyReleased(int key) const noexcept;

        private:
            GLFWwindow* window_;
            std::array<bool, kKeyCount> currentKeys_{};
            std::array<bool, kKeyCount> previousKeys_{};
    };
} // namespace stubai::core

#endif // STUBAI_CORE_INPUT_HPP