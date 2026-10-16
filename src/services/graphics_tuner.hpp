#pragma once

#include <string>
#include <unordered_map>

namespace gta5opt::services {

class MemoryService;
class SignatureService;

class GraphicsTuner {
public:
    GraphicsTuner(MemoryService& mem, SignatureService& sigs);

    bool apply_profile(const std::string& profile_name);
    bool revert();

private:
    MemoryService& mem_;
    SignatureService& sigs_;
    std::unordered_map<std::string, int> original_fps_cap_;
};

} // namespace gta5opt::services