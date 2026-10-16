#pragma once

#include <string>
#include <cstdint>
#include <optional>

namespace gta5opt::services {

class MemoryService {
public:
    bool attach(const std::string& process_name);
    void detach();
    bool is_attached() const { return handle_ != nullptr; }

    std::optional<uintptr_t> resolve(const std::string& module, const std::string& pattern, int offset);
    bool read(uintptr_t addr, void* out, size_t size) const;
    bool write(uintptr_t addr, const void* in, size_t size) const;

private:
    void* handle_ = nullptr;
    uint32_t pid_ = 0;
};

} // namespace gta5opt::services