#include "handlers/overlay_handler.hpp"
#include "services/overlay_service.hpp"
#include "utils/logger.hpp"

namespace gta5opt::handlers {

std::string OverlayHandler::handle_command(const std::string& cmd) {
    auto& svc = services::OverlayService::instance();

    if (cmd == "toggle_fps") {
        svc.toggle_fps_counter();
        return "ok";
    }
    if (cmd == "toggle_frametime") {
        svc.toggle_frametime_graph();
        return "ok";
    }
    if (cmd == "reload_profile") {
        LOG_INFO("overlay asked for profile reload");
        return "queued";
    }
    return "unknown";
}

} // namespace gta5opt::handlers