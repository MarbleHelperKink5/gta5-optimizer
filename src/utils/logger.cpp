#include "utils/logger.hpp"

#include <chrono>
#include <ctime>

namespace gta5opt::utils {

Logger& Logger::instance() {
    static Logger l;
    return l;
}

Logger::Logger() {
    file_.open("logs/optimizer.log", std::ios::app);
}

void Logger::log(Level lvl, const std::string& msg) {
    if (lvl == Level::Debug && !verbose_) return;

    const char* tag = "INFO";
    switch (lvl) {
        case Level::Debug: tag = "DEBUG"; break;
        case Level::Info:  tag = "INFO";  break;
        case Level::Warn:  tag = "WARN";  break;
        case Level::Error: tag = "ERROR"; break;
    }

    std::lock_guard<std::mutex> lock(mtx_);
    if (file_) file_ << "[" << tag << "] " << msg << "\n";
    std::printf("[%s] %s\n", tag, msg.c_str());
}

} // namespace gta5opt::utils