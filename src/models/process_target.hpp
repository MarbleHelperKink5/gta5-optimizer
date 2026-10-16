#pragma once

#include <string>
#include <cstdint>

namespace gta5opt::models {

struct ProcessTarget {
    std::string name;
    uint32_t pid = 0;
    uintptr_t base = 0;
    size_t size = 0;

    bool valid() const { return pid != 0 && base != 0; }
};

} // namespace gta5opt::models