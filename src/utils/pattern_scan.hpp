#pragma once

#include <string>
#include <optional>
#include <cstdint>

namespace gta5opt::utils {

std::optional<uintptr_t> scan_pattern(void* process_handle,
                                      uintptr_t base,
                                      size_t size,
                                      const std::string& pattern);

} // namespace gta5opt::utils