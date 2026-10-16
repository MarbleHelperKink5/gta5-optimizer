#include "services/overlay_service.hpp"
#include "adapters/dxgi_adapter.hpp"
#include "utils/logger.hpp"

namespace gta5opt::services {

OverlayService& OverlayService::instance() {
    static OverlayService svc;
    return svc;
}

void OverlayService::start() {
    if (running_) return;
    if (!adapters::dxgi_hook_install()) {
        LOG_WARN("dxgi hook install failed; overlay disabled");
        return;
    }
    running_ = true;
    LOG_INFO("overlay started");
}

void OverlayService::stop() {
    if (!running_) return;
    adapters::dxgi_hook_remove();
    running_ = false;
    LOG_INFO("overlay stopped");
}

void OverlayService::tick() {
    if (!running_) return;
    adapters::dxgi_present_frame(show_fps_, show_frametime_);
}

void OverlayService::toggle_fps_counter() { show_fps_ = !show_fps_; }
void OverlayService::toggle_frametime_graph() { show_frametime_ = !show_frametime_; }

} // namespace gta5opt::services