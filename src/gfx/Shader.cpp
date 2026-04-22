#include "gfx/Shader.hpp"
#include "core/Logger.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace stubai::gfx {

    namespace {
        GLenum toGL(ShaderStage stage) {
            switch(stage) {
                case ShaderStage::Vertex: return GL_VERTEX_SHADER;
                case ShaderStage::Fragment: return GL_FRAGMENT_SHADER;
            }
            return 0;
        }
    

    std::string readFile(const std::filesystem::path& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw  std::runtime_error("Cannot open shader file: " + path.string());
        }
        std::ostringstream oss;
        oss << file.rdbuf();
        return oss.str();
    }

    GLuint compileStage(GLenum type, const std::string& src, const std::string& path) {
        const GLuint shader = glCreateShader(type);
        const char* srcCStr = src.c_str();
        glShaderSource(shader, 1, &srcCStr, nullptr);
        glCompileShader(shader);

        GLint ok = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
        if (ok == GL_FALSE) {
            GLint len = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
            std::string log(static_cast<std::size_t>(len), '\0');
            glGetShaderInfoLog(shader, len, nullptr, log.data());
            glDeleteShader(shader);
            throw std::runtime_error("Compile error in shader " + path + ": " + log);
        }
        return shader;
    } 

    } // namespace

    Shader::Shader(std::initializer_list<ShaderStageSource> stages) {
        std::vector<GLuint> handles;
        handles.reserve(stages.size());

        try {
            for (const auto& s : stages) {
                const std::string src = readFile(s.path);
                handles.push_back(compileStage(toGL(s.stage), src, s.path.string()));
            }

            program_ = glCreateProgram();
            for (auto h : handles) { glAttachShader(program_, h); }
            glLinkProgram(program_);

            GLint ok = 0;
            glGetProgramiv(program_, GL_LINK_STATUS, &ok);
            if (ok == GL_FALSE) {
                GLint len = 0;
                glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &len);
                std::string log(static_cast<std::size_t>(len), '\0');
                glGetProgramInfoLog(program_, len, nullptr, log.data());
                throw std::runtime_error("Link error:\n" + log);
            }

            for (auto h: handles) {
                glDetachShader(program_, h);
                glDeleteShader(h);
            }
            STUBAI_LOG_INFO("Shader linked: program={}", program_);
        } catch(...) {
            for (auto h: handles) { glDeleteShader(h);}
            if (program_ != 0) {
                glDeleteProgram(program_);
                program_ = 0;
            }
            throw;
        }
    }

    Shader::~Shader() {
        if (program_ != 0) {
            glDeleteProgram(program_);
        }
    }

    void Shader::bind() const { glUseProgram(program_); }
    void Shader::unbind() { glUseProgram(0); }
} // namespace stubai::gfx

