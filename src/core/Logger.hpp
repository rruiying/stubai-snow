#ifndef STUBAI_CORE_LOGGER_HPP
#define STUBAI_CORE_LOGGER_HPP

#include <spdlog/spdlog.h>

namespace stubai::core {
    
    class Logger {
        public:
            static void init(const char* name="stubai");

            [[nodiscard]] static spdlog::logger& get();
    };
} // namespace stubai::core

#define STUBAI_LOG_TRACE(...) ::stubai::core::Logger::get().trace(__VA_ARGS__)
#define STUBAI_LOG_DEBUG(...) ::stubai::core::Logger::get().debug(__VA_ARGS__)
#define STUBAI_LOG_INFO(...)  ::stubai::core::Logger::get().info(__VA_ARGS__)
#define STUBAI_LOG_WARN(...)  ::stubai::core::Logger::get().warn(__VA_ARGS__)
#define STUBAI_LOG_ERROR(...) ::stubai::core::Logger::get().error(__VA_ARGS__)

#endif // STUBAI_CORE_LOGGER_HPP