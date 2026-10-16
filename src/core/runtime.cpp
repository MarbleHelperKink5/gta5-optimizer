#include "core/runtime.hpp"
#include "services/signature_service.hpp"
#include "services/memory_service.hpp"
#include "services/graphics_tuner.hpp"
#include "services/overlay_service.hpp"
#include "utils/logger.hpp"

namespace gta5opt::core {

Runtime& Runtime::instance() {
    static Runtime rt;
    return rt;
}

bool Runtime::configure(const RuntimeConfig& cfg) {
    cfg_ = cfg;
    signatures_ = std::make_unique<services::SignatureService>("config/signatures.ini");
    memory_     = std::make_unique<services::MemoryService>();
    tuner_      = std::make_unique<services::GraphicsTuner>(*memory_, *signatures_);
    overlay_    = std::make_unique<services::OverlayService>();

    if (!signatures_->load()) {
        LOG_ERROR("failed to load signature table");
        return false;
    }
    if (!memory_->attach(cfg_.process_name)) {
        LOG_ERROR("could not attach to {}", cfg_.process_name);
        return false;
    }
    return true;
}

int Runtime::run() {
    running_ = true;
    LOG_INFO("runtime loop entered");

    if (!tuner_->apply_profile(cfg_.profile_name)) {
        LOG_WARN("profile {} not applied", cfg_.profile_name);
    }

    if (cfg_.attach_overlay) {
        overlay_->start();
    }

    while (running_) {
        overlay_->tick();
        // main loop is intentionally minimal; services drive their own work
    }
    return 0;
}

void Runtime::shutdown() {
    running_ = false;
    if (overlay_) overlay_->stop();
    if (memory_)  memory_->detach();
    LOG_INFO("runtime shutdown complete");
}

} // namespace gta5opt::core