#include "core/bootstrap.hpp"
#include "core/runtime.hpp"
#include "utils/logger.hpp"

namespace gta5opt::core {

Bootstrap::Bootstrap(BootstrapOptions opts) : opts_(std::move(opts)) {}

Bootstrap::~Bootstrap() {
    if (initialized_) shutdown();
}

bool Bootstrap::initialize() {
    utils::Logger::instance().set_verbose(opts_.verbose);
    LOG_INFO("gta5-optimizer bootstrap starting");
    LOG_INFO("target process: {}", opts_.process_name);
    LOG_INFO("profile: {}", opts_.profile);

    RuntimeConfig cfg;
    cfg.process_name = opts_.process_name;
    cfg.profile_name = opts_.profile;
    cfg.attach_overlay = opts_.attach_overlay;

    if (!Runtime::instance().configure(cfg)) {
        LOG_ERROR("runtime configuration failed");
        return false;
    }

    initialized_ = true;
    return true;
}

int Bootstrap::run() {
    if (!initialized_) return -1;
    return Runtime::instance().run();
}

void Bootstrap::shutdown() {
    Runtime::instance().shutdown();
    initialized_ = false;
}

} // namespace gta5opt::core