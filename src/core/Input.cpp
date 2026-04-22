#include "core/Input.hpp"

#include <GLFW/glfw3.h>

namespace stubai::core {
    Input::Input(GLFWwindow* window) : window_(window) {}

    void Input::update() {
        previousKeys_ = currentKeys_;
        for (int i = 0; i < kKeyCount; ++i) {
            currentKeys_[static_cast<std::size_t>(i)] =
            glfwGetKey(window_, i) == GLFW_PRESS;
        }
    }

    bool Input::isKeyDown(int key) const noexcept {
        if (key < 0 || key >= kKeyCount) { return false; }
        return currentKeys_[static_cast<std::size_t>(key)];
    }

    bool Input::wasKeyPressed(int key) const noexcept {
        if (key < 0 || key >= kKeyCount) { return false; }
        const auto i = static_cast<std::size_t>(key);
        return currentKeys_[i] && !previousKeys_[i];
    }

    bool Input::wasKeyReleased(int key) const noexcept {
        if (key < 0 || key >= kKeyCount) { return false; }
        const auto i = static_cast<std::size_t>(key);
        return !currentKeys_[i] && previousKeys_[i];
    }
} // namespace stubai::core
