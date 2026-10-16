#pragma once

#include <string>

namespace gta5opt::handlers {

class OverlayHandler {
public:
    std::string handle_command(const std::string& cmd);
};

} // namespace gta5opt::handlers