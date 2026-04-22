#include "scene/Camera.hpp"

#include "core/Input.hpp"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

namespace stubai::scene {
    namespace {
        constexpr float kHalfPi = 1.5707963f;
        constexpr float kPitchEpsilon = 0.01f;
    }

    Camera::Camera(const CameraDesc& desc) : desc_(desc), position_(desc.position) {
        const glm::vec3 dir = glm::normalize(desc_.target - desc_.position);
        pitch_ = std::asin(dir.y);
        yaw_ = std::atan2(dir.z, dir.x);
    }

    glm::vec3 Camera::forward() const {
        return {std::cos(pitch_) * std::cos(yaw_),
                std::sin(pitch_),
                std::cos(pitch_) * std::sin(yaw_)};
    }

    glm::vec3 Camera::right() const {
        return glm::normalize(glm::cross(forward(), desc_.up));
    }

    glm::mat4 Camera::view() const {
        return glm::lookAt(position_, position_ + forward(), desc_.up);
    }

    glm::mat4 Camera::projection() const {
        return glm::perspective(desc_.fovY, desc_.aspect, desc_.nearPlane, desc_.farPlane);
    }

    void Camera::update(const core::Input& input, float deltaTime) {
        if (input.isCursorLocked()) {
            const glm::vec2 d = input.mouseDelta();
            yaw_ += d.x * desc_.mouseSensitivity;
            pitch_ -= d.y * desc_.mouseSensitivity;
            pitch_ = std::clamp(pitch_, -kHalfPi + kPitchEpsilon, kHalfPi - kPitchEpsilon);
        }

        const glm::vec3 fwd = forward();
        const glm::vec3 rgt = right();
        glm::vec3 move{0.0f};
        if (input.isKeyDown(GLFW_KEY_W)) { move += fwd; }
        if (input.isKeyDown(GLFW_KEY_S)) { move -= fwd; }
        if (input.isKeyDown(GLFW_KEY_D)) { move += rgt; }
        if (input.isKeyDown(GLFW_KEY_A)) { move -= rgt; }
        if (input.isKeyDown(GLFW_KEY_E)) { move += desc_.up; }
        if (input.isKeyDown(GLFW_KEY_Q)) { move -= desc_.up; }
        if (glm::length(move) > 0.0f) { move = glm::normalize(move); }

        const float speedMul = input.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 5.0f : 1.0f;
        position_ += move * (desc_.moveSpeed * speedMul * deltaTime);
    }
    
}