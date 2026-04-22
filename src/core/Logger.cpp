#include "core/Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace stubai::core {

    namespace {
        std::shared_ptr<spdlog::logger> g_logger;
    }

    void Logger::init(const char* name) {
        if (g_logger) { return; }
        g_logger = spdlog::stdout_color_mt(name);
        g_logger->set_pattern("[%H:%M:%S.%e] [%^%l%$] [%n] %v");

        #ifdef NDEBUG
            g_logger->set_level(spdlog::level::info);
        #else
            g_logger->set_level(spdlog::level::debug);
        #endif
            spdlog::set_default_logger(g_logger);
    }

    spdlog::logger& Logger::get() {
        if (!g_logger) { init(); }
        return *g_logger;
    }
}