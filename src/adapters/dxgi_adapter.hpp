#pragma once

namespace gta5opt::adapters {

bool dxgi_hook_install();
void dxgi_hook_remove();
void dxgi_present_frame(bool show_fps, bool show_frametime);

} // namespace gta5opt::adapters