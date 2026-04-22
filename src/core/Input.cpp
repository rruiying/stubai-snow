#include "core/Input.hpp"

#include <GLFW/glfw3.h>

namespace stubai::core {
    Input::Input(GLFWwindow* window) : window_(window) {
        double x = 0.0, y = 0.0;
        glfwGetCursorPos(window_, &x, &y);
        mousePos_ = prevMousePos_ = {static_cast<float>(x), static_cast<float>(y)};
    }

    void Input::update() {
        previousKeys_ = currentKeys_;
        prevMousePos_ = mousePos_;

        for (int i = 0; i < kKeyCount; ++i) {
            currentKeys_[static_cast<std::size_t>(i)] =
            glfwGetKey(window_, i) == GLFW_PRESS;
        }
        for (int b = 0; b < kMouseButtonCount; ++b) {
            mouseButtons_[static_cast<std::size_t>(b)] =
            glfwGetMouseButton(window_, b) == GLFW_PRESS;
        }
        double x = 0.0, y = 0.0;
        glfwGetCursorPos(window_, &x, &y);
        mousePos_ = {static_cast<float>(x), static_cast<float>(y)};
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

    bool Input::isMouseDown(int button) const noexcept {
        if (button < 0 || button >= kMouseButtonCount) { return false; }
        return mouseButtons_[static_cast<std::size_t>(button)];
    }

    void Input::setCursorLocked(bool locked) {
        cursorLocked_ = locked;
        glfwSetInputMode(window_, GLFW_CURSOR,
            locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        if (glfwRawMouseMotionSupported() != 0) {
            glfwSetInputMode(window_, GLFW_RAW_MOUSE_MOTION, locked ? GLFW_TRUE : GLFW_FALSE);
        }
    }
} // namespace stubai::core
