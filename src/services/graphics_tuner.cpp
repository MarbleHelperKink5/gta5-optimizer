#include "services/graphics_tuner.hpp"
#include "services/memory_service.hpp"
#include "services/signature_service.hpp"
#include "utils/logger.hpp"

namespace gta5opt::services {

GraphicsTuner::GraphicsTuner(MemoryService& mem, SignatureService& sigs)
    : mem_(mem), sigs_(sigs) {}

bool GraphicsTuner::apply_profile(const std::string& profile_name) {
    LOG_INFO("applying graphics profile '{}'", profile_name);

    auto* sig = sigs_.find("fps_cap");
    if (!sig) {
        LOG_WARN("fps_cap signature missing; skipping");
        return false;
    }

    auto addr = mem_.resolve(sig->module, sig->pattern, sig->offset);
    if (!addr) {
        LOG_WARN("fps_cap address not resolved");
        return false;
    }

    int current = 0;
    mem_.read(*addr, &current, sizeof(current));
    original_fps_cap_[profile_name] = current;

    int target = (profile_name == "performance") ? 240 : 144;
    if (!mem_.write(*addr, &target, sizeof(target))) {
        LOG_ERROR("failed to write fps cap");
        return false;
    }
    LOG_INFO("fps cap {} -> {}", current, target);
    return true;
}

bool GraphicsTuner::revert() {
    for (auto& [name, original] : original_fps_cap_) {
        auto* sig = sigs_.find("fps_cap");
        if (!sig) continue;
        auto addr = mem_.resolve(sig->module, sig->pattern, sig->offset);
        if (addr) mem_.write(*addr, &original, sizeof(original));
    }
    original_fps_cap_.clear();
    return true;
}

} // namespace gta5opt::services