#pragma once

#include <string>
#include <memory>

namespace gta5opt::services { class SignatureService; class MemoryService; class GraphicsTuner; class OverlayService; }

namespace gta5opt::core {

struct RuntimeConfig {
    std::string process_name;
    std::string profile_name;
    bool attach_overlay = true;
};

class Runtime {
public:
    static Runtime& instance();

    bool configure(const RuntimeConfig& cfg);
    int run();
    void shutdown();

private:
    Runtime() = default;
    RuntimeConfig cfg_;
    bool running_ = false;

    std::unique_ptr<services::SignatureService> signatures_;
    std::unique_ptr<services::MemoryService>    memory_;
    std::unique_ptr<services::GraphicsTuner>    tuner_;
    std::unique_ptr<services::OverlayService>   overlay_;
};

} // namespace gta5opt::core