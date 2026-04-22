#include "core/Window.hpp"
#include "core/Logger.hpp"
#include "core/Time.hpp"
#include "core/Input.hpp"
#include "gfx/GLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main() {
    try {
        stubai::core::Logger::init();
        STUBAI_LOG_INFO("Starting Stubai Snow");

        stubai::core::WindowDesc desc{};
        desc.width = 1600;
        desc.height = 900;
        desc.title = "Stubai Snow";
        stubai::core::Window window(desc);

        stubai::gfx::GLContext::initialize(/*installDebugOutput=*/true);

        stubai::core::Input input(window.handle());
        stubai::core::Time time;

        STUBAI_LOG_INFO("Window created. Close to exit.");

        std::uint64_t lastFpsFrame = 0;

        while (!window.shouldClose()) {
            window.pollEvents();
            input.update();
            time.tick();
            
            if (input.wasKeyPressed(GLFW_KEY_ESCAPE)) {
                STUBAI_LOG_INFO("ESC pressed, exiting");
                glfwSetWindowShouldClose(window.handle(), GLFW_TRUE);
            }

            glClearColor(0.72f, 0.76f, 0.80f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            window.swapBuffers();

            if (time.frameCount() - lastFpsFrame >= 60) {
                STUBAI_LOG_DEBUG("frame={} fps={:.1f}",
                    time.frameCount(),
                    time.fps()
                );
                lastFpsFrame = time.frameCount();
            }
        }
        STUBAI_LOG_INFO("Stubai Snow shutting down");
        return 0;
    } catch (const std::exception& e) {
        STUBAI_LOG_ERROR("Fatal error: {}", e.what());
        return 1;
    }
}