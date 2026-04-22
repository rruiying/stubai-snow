#include "core/Window.hpp"

#include <iostream>

int main() {
    try {
        stubai::core::WindowDesc desc{};
        desc.width = 1600;
        desc.height = 900;
        desc.title = "Stubai Snow";
        stubai::core::Window window(desc);

        std::cout << "Window created. Close to exit.\n";

        while (!window.shouldClose()) {
            window.pollEvents();
            window.swapBuffers();
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}