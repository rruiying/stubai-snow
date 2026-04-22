#include "core/Window.hpp"
#include "core/Logger.hpp"
#include "core/Time.hpp"
#include "core/Input.hpp"
#include "gfx/GLContext.hpp"
#include "gfx/Shader.hpp"
#include "scene/Camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>

int main() {
    try {
        stubai::core::Logger::init();
        STUBAI_LOG_INFO("Starting Stubai Snow");

        stubai::core::WindowDesc desc{};
        desc.width = 1600;
        desc.height = 900;
        desc.title = "Stubai Snow";
        stubai::core::Window window(desc);

        stubai::gfx::GLContext::initialize(true);

        stubai::core::Input input(window.handle());
        stubai::core::Time time;

        stubai::scene::CameraDesc cd{};
        cd.position = {0.0f, 5.0f, 10.0f};
        cd.target   = {0.0f, 0.0f, 0.0f};
        cd.aspect   = window.aspect();
        stubai::scene::Camera camera(cd);

        const std::filesystem::path assets{STUBAI_ASSETS_DIR};
        stubai::gfx::Shader shader{{
            {stubai::gfx::ShaderStage::Vertex,   assets / "shaders/test/hello_triangle.vert"},
            {stubai::gfx::ShaderStage::Fragment, assets / "shaders/test/hello_triangle.frag"},
        }};

        GLuint emptyVao = 0;
        glGenVertexArrays(1, &emptyVao);

        STUBAI_LOG_INFO("Window created. Close to exit.");

        std::uint64_t lastFpsFrame = 0;

        while (!window.shouldClose()) {
            window.pollEvents();
            input.update();
            const float dt = time.tick();
            
            if (input.wasKeyPressed(GLFW_KEY_ESCAPE)) {
                STUBAI_LOG_INFO("ESC pressed, exiting");
                glfwSetWindowShouldClose(window.handle(), GLFW_TRUE);
            }

            input.setCursorLocked(input.isMouseDown(GLFW_MOUSE_BUTTON_RIGHT));
            camera.update(input, dt);

            glClearColor(0.72f, 0.76f, 0.80f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.bind();
            glBindVertexArray(emptyVao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            window.swapBuffers();

            if (time.frameCount() - lastFpsFrame >= 60) {
                const auto p = camera.position();
                STUBAI_LOG_DEBUG("frame={} fps={:.1f} cam=({:.1f}, {:.1f}, {:.1f})",
                    time.frameCount(),
                    time.fps(),
                    p.x, p.y, p.z
                );
                lastFpsFrame = time.frameCount();
            }
        }
        glDeleteVertexArrays(1, &emptyVao);
        STUBAI_LOG_INFO("Stubai Snow shutting down");
        return 0;
    } catch (const std::exception& e) {
        STUBAI_LOG_ERROR("Fatal error: {}", e.what());
        return 1;
    }
}