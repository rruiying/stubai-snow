#ifndef STUBAI_GFX_SHADER_HPP
#define STUBAI_GFX_SHADER_HPP

#include <string>
#include <filesystem>
#include <initializer_list>
#include <cstdint>

namespace stubai::gfx {

    enum class ShaderStage : std::uint8_t {
        Vertex,
        Fragment,
    };

    struct ShaderStageSource {
        ShaderStage stage;
        std::filesystem::path path;
    };

    class Shader {
        public:
            explicit Shader(std::initializer_list<ShaderStageSource> source);
            ~Shader();

            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;

            void bind() const;
            static void unbind();

            [[nodiscard]] std::uint32_t handle() const noexcept {return program_; }

        private:
            std::uint32_t program_ = 0;
    };

} // namespace stubai::gfx

#endif // STUBAI_GFX_SHADER_HPP