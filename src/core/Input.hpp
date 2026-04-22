#ifndef STUBAI_CORE_INPUT_HPP
#define STUBAI_CORE_INPUT_HPP

#include <array>

#include <glm/vec2.hpp>

struct GLFWwindow;

namespace stubai::core {

    class Input {
        public:
            static constexpr int kKeyCount = 512;
            static constexpr int kMouseButtonCount = 8;

            explicit Input(GLFWwindow* window);

            void update();

            [[nodiscard]] bool isKeyDown(int key) const noexcept;
            [[nodiscard]] bool wasKeyPressed(int key) const noexcept;
            [[nodiscard]] bool wasKeyReleased(int key) const noexcept;

            [[nodiscard]] bool isMouseDown(int glfwButton) const noexcept;
            [[nodiscard]] glm::vec2 mousePosition() const noexcept {return mousePos_;}
            [[nodiscard]] glm::vec2 mouseDelta() const noexcept {return mousePos_ - prevMousePos_; }

            void setCursorLocked(bool locked);
            [[nodiscard]] bool isCursorLocked() const noexcept { return cursorLocked_;}

        private:
            GLFWwindow* window_;
            std::array<bool, kKeyCount> currentKeys_{};
            std::array<bool, kKeyCount> previousKeys_{};
            std::array<bool, kMouseButtonCount>  mouseButtons_{};
            glm::vec2 mousePos_{0.0f};
            glm::vec2 prevMousePos_{0.0f};
            bool cursorLocked_ = false;
    };
} // namespace stubai::core

#endif // STUBAI_CORE_INPUT_HPP