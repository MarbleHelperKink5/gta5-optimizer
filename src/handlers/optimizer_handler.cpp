#include "handlers/optimizer_handler.hpp"
#include "services/graphics_tuner.hpp"
#include "utils/logger.hpp"

namespace gta5opt::handlers {

OptimizerHandler::OptimizerHandler(services::GraphicsTuner& tuner) : tuner_(tuner) {}

bool OptimizerHandler::apply(const std::string& profile) {
    LOG_INFO("handler: apply profile {}", profile);
    return tuner_.apply_profile(profile);
}

bool OptimizerHandler::revert() {
    LOG_INFO("handler: revert tuning");
    return tuner_.revert();
}

} // namespace gta5opt::handlers