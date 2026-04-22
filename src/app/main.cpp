#include "core/Window.hpp"
#include "gfx/GLContext.hpp"

#include <glad/glad.h>


#include <iostream>

int main() {
    try {
        stubai::core::WindowDesc desc{};
        desc.width = 1600;
        desc.height = 900;
        desc.title = "Stubai Snow";
        stubai::core::Window window(desc);

        stubai::gfx::GLContext::initialize(/*installDebugOutput=*/true);

        std::cout << "Window created. Close to exit.\n";

        while (!window.shouldClose()) {
            window.pollEvents();
            
            glClearColor(0.72f, 0.76f, 0.80f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            window.swapBuffers();
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}