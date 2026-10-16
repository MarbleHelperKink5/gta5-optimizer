#pragma once

#include <string>

namespace gta5opt::services { class GraphicsTuner; }

namespace gta5opt::handlers {

class OptimizerHandler {
public:
    explicit OptimizerHandler(services::GraphicsTuner& tuner);
    bool apply(const std::string& profile);
    bool revert();

private:
    services::GraphicsTuner& tuner_;
};

} // namespace gta5opt::handlers