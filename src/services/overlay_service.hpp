#pragma once

namespace gta5opt::services {

class OverlayService {
public:
    static OverlayService& instance();

    void start();
    void stop();
    void tick();

    void toggle_fps_counter();
    void toggle_frametime_graph();

private:
    OverlayService() = default;
    bool running_ = false;
    bool show_fps_ = true;
    bool show_frametime_ = false;
};

} // namespace gta5opt::services