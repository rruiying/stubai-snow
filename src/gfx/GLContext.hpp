#ifndef STUBAI_GFX_GL_CONTEXT_HPP
#define STUBAI_GFX_GL_CONTEXT_HPP

namespace stubai::gfx {

class GLContext {
    public:
        static void initialize(bool installDebugOutput = true);
};

} // namespace stubai::gfx

#endif // STUBAI_GFX_GL_CONTEXT_HPP