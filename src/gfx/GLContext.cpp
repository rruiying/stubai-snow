#include "gfx/GLContext.hpp"

#include <glad/glad.h>

#include <iostream>

namespace stubai::gfx {

namespace {

    const char* sourceString(GLenum source) {
        switch (source) {
            case GL_DEBUG_SOURCE_API: return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
            case GL_DEBUG_SOURCE_APPLICATION: return "Application";
            default: return "Other";
        }
    }

    const char* typeString(GLenum type) {
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:               return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "UndefinedBehavior";
    case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
    case GL_DEBUG_TYPE_MARKER:              return "Marker";
    default:                                return "Other";
        }
    }

    const char* severityString(GLenum severity) {
        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         return "HIGH";
        case GL_DEBUG_SEVERITY_MEDIUM:       return "MED ";
        case GL_DEBUG_SEVERITY_LOW:          return "LOW ";
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "INFO";
        default:                             return "??? ";
        }
    }

    void GLAPIENTRY debugCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei /*length*/, const GLchar* message, const void* /*userParam*/)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
        return;
    }
    std::cerr << "[GL " << severityString(severity) << "][" << sourceString(source)
              << "/" << typeString(type) << "][id=" << id << "] " << message << "\n";
}

}  // namespace

void GLContext::initialize(bool installDebugOutput) {
    if (installDebugOutput) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(&debugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
                              0, nullptr, GL_TRUE);

        std::cout << "GL KHR_debug installed\n";
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}
}