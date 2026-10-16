#pragma once

#include <string>
#include <vector>

namespace gta5opt::models {

struct TuningProfile {
    std::string name;
    std::string description;
    int fps_cap = 144;
    bool disable_motion_blur = false;
    bool disable_dof = false;
    int msaa = 0;
    bool aggressive_gc = false;

    static TuningProfile parse(const std::string& ini_path);
    static std::vector<std::string> list_available(const std::string& dir);
};

} // namespace gta5opt::models