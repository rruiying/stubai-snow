#ifndef STUBAI_SCENE_CAMERA_HPP
#define STUBAI_SCENE_CAMERA_HPP

#include <glm/glm.hpp>

namespace stubai::core { class Input;}

namespace stubai::scene {

    struct CameraDesc {
        glm::vec3 position {0.0f, 0.0f, 5.0f};
        glm::vec3 target {0.0f, 0.0f, 0.0f};
        glm::vec3 up {0.0f, 1.0f, 0.0f};
        float fovY = 1.0472f;
        float aspect = 16.0f / 9.0f;
        float nearPlane = 0.1f;
        float farPlane = 5000.0f;
        float moveSpeed = 5.0f;
        float mouseSensitivity = 0.002f;
    };

    class Camera {
        public:
            explicit Camera(const CameraDesc& desc);

            void update(const core::Input& input, float deltaTime);

            void setAspect(float aspect) { desc_.aspect = aspect;}
            
            [[nodiscard]] glm::mat4 view() const;
            [[nodiscard]] glm::mat4 projection() const;
            [[nodiscard]] glm::mat4 viewProjection() const { return projection() * view(); }

            [[nodiscard]] const glm::vec3& position() const noexcept { return position_; }
            [[nodiscard]] glm::vec3 forward() const;
            [[nodiscard]] glm::vec3 right() const;

        private:
            CameraDesc desc_;
            glm::vec3 position_ {0.0f};
            float yaw_ = 0.0f;
            float pitch_ = 0.0f;
    };
} // namespace stubai::scene

#endif // STUBAI_SCENE_CAMERA_HPP