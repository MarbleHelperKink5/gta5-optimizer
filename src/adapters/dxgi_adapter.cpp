#include "adapters/dxgi_adapter.hpp"
#include "utils/logger.hpp"

#include <d3d11.h>
#include <dxgi.h>

namespace gta5opt::adapters {

namespace {
    bool g_installed = false;
    IDXGISwapChain* g_swapchain = nullptr;
}

bool dxgi_hook_install() {
    if (g_installed) return true;
    // Real implementation would vtable-hook IDXGISwapChain::Present.
    // Stubbed here so the service layer can be compiled and tested.
    LOG_INFO("dxgi hook: placeholder install");
    g_installed = true;
    return true;
}

void dxgi_hook_remove() {
    g_installed = false;
    g_swapchain = nullptr;
}

void dxgi_present_frame(bool show_fps, bool show_frametime) {
    if (!g_installed) return;
    // Overlay render pass would draw the FPS/frametime text here.
    (void)show_fps;
    (void)show_frametime;
}

} // namespace gta5opt::adapters