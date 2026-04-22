#ifndef STUBAI_CORE_WINDOW_HPP
#define STUBAI_CORE_WINDOW_HPP

#include <cstdint>
#include <string>

struct GLFWwindow;

namespace stubai::core {

    struct WindowDesc {
        std::uint32_t width = 1600;
        std::uint32_t height = 900;
        std::string title = "Stubai Snow";
    };

    class Window {
        public:
            explicit Window(const WindowDesc& desc);
            ~Window();

            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

            [[nodiscard]] bool shouldClose() const;
            void pollEvents();
            void swapBuffers();

            [[nodiscard]] std::uint32_t width() const noexcept {return width_;}
            [[nodiscard]] std::uint32_t height() const noexcept {return height_;}
            [[nodiscard]] float aspect() const noexcept {
                return static_cast<float>(width_) / static_cast<float>(height_);
            }
            [[nodiscard]] GLFWwindow* handle() const noexcept {return handle_;}

        private:
            GLFWwindow* handle_ = nullptr;
            std::uint32_t width_ = 0;
            std::uint32_t height_ = 0;
    };
} // namespace stubai::core

#endif // STUBAI_CORE_WINDOW_HPP