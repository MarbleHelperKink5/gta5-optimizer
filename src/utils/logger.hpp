#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <cstdio>

namespace gta5opt::utils {

enum class Level { Debug, Info, Warn, Error };

class Logger {
public:
    static Logger& instance();

    void set_verbose(bool v) { verbose_ = v; }
    void log(Level lvl, const std::string& msg);

    template <typename... Args>
    void logf(Level lvl, const char* fmt, Args... args) {
        char buf[1024];
        std::snprintf(buf, sizeof(buf), fmt, args...);
        log(lvl, buf);
    }

private:
    Logger();
    bool verbose_ = false;
    std::ofstream file_;
    std::mutex mtx_;
};

} // namespace gta5opt::utils

#define LOG_INFO(...)  ::gta5opt::utils::Logger::instance().logf(::gta5opt::utils::Level::Info,  __VA_ARGS__)
#define LOG_WARN(...)  ::gta5opt::utils::Logger::instance().logf(::gta5opt::utils::Level::Warn,  __VA_ARGS__)
#define LOG_ERROR(...) ::gta5opt::utils::Logger::instance().logf(::gta5opt::utils::Level::Error, __VA_ARGS__)
#define LOG_DEBUG(...) ::gta5opt::utils::Logger::instance().logf(::gta5opt::utils::Level::Debug, __VA_ARGS__)