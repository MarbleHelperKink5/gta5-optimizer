#include "services/memory_service.hpp"
#include "adapters/win32_process_adapter.hpp"
#include "utils/pattern_scan.hpp"
#include "utils/logger.hpp"

namespace gta5opt::services {

bool MemoryService::attach(const std::string& process_name) {
    auto pid = adapters::find_process_by_name(process_name);
    if (!pid) {
        LOG_ERROR("process {} not running", process_name);
        return false;
    }
    pid_ = *pid;
    handle_ = adapters::open_process_for_rw(pid_);
    if (!handle_) {
        LOG_ERROR("OpenProcess failed (err={})", adapters::last_error());
        return false;
    }
    LOG_INFO("attached to {} (pid {})", process_name, pid_);
    return true;
}

void MemoryService::detach() {
    if (handle_) {
        adapters::close_handle(handle_);
        handle_ = nullptr;
    }
}

std::optional<uintptr_t> MemoryService::resolve(const std::string& module,
                                                const std::string& pattern,
                                                int offset) {
    if (!handle_) return std::nullopt;
    auto base = adapters::module_base(pid_, module);
    auto size = adapters::module_size(pid_, module);
    if (!base || !size) return std::nullopt;

    auto hit = utils::scan_pattern(handle_, *base, *size, pattern);
    if (!hit) return std::nullopt;
    return *hit + offset;
}

bool MemoryService::read(uintptr_t addr, void* out, size_t size) const {
    return adapters::read_memory(handle_, addr, out, size);
}

bool MemoryService::write(uintptr_t addr, const void* in, size_t size) const {
    return adapters::write_memory(handle_, addr, in, size);
}

} // namespace gta5opt::services