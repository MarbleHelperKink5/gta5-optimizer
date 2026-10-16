add_library(gta5opt_core STATIC
    core/bootstrap.cpp
    core/runtime.cpp
    handlers/overlay_handler.cpp
    handlers/optimizer_handler.cpp
    services/signature_service.cpp
    services/memory_service.cpp
    services/graphics_tuner.cpp
    services/overlay_service.cpp
    models/process_target.cpp
    models/tuning_profile.cpp
    adapters/win32_process_adapter.cpp
    adapters/dxgi_adapter.cpp
    utils/logger.cpp
    utils/pattern_scan.cpp
)

target_include_directories(gta5opt_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gta5opt_core PUBLIC d3d11 dxgi psapi)