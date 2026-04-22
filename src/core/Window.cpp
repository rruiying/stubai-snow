#include "core/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

namespace stubai::core {

namespace{
    int g_glfwRefCount = 0;

    void initGlfw() {
        if (g_glfwRefCount++ == 0) {
            if (glfwInit() == GLFW_FALSE) {
                throw std::runtime_error("glfwInit failed");
            }
        }
    }

    void shutdownGlfw() {
        if(--g_glfwRefCount == 0) {
            glfwTerminate();
        }
    }
}

Window::Window(const WindowDesc& desc)
    : width_(desc.width), height_(desc.height) {
        initGlfw();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        handle_ = glfwCreateWindow(
            static_cast<int>(desc.width),
            static_cast<int>(desc.height),
            desc.title.c_str(),
            nullptr,
            nullptr
        );

        if (handle_ == nullptr) {
            shutdownGlfw();
            throw std::runtime_error("glfwCreateWindow failed");
        }

        glfwMakeContextCurrent(handle_);
        glfwSwapInterval(1);

        if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
            glfwDestroyWindow(handle_);
            shutdownGlfw();
            throw std::runtime_error("gladLoadGLLoader failed");
        }

        std::cout << "OpenGL: " << glGetString(GL_VERSION) << "\n";
        std::cout << "GPU: " << glGetString(GL_RENDERER) << "\n";
    }

    Window::~Window() {
        if (handle_ != nullptr) {
            glfwDestroyWindow(handle_);
        }
        shutdownGlfw();
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(handle_) != 0;
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(handle_);
    }

} // namespace stubai::core