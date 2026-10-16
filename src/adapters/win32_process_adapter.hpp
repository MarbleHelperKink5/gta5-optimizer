#pragma once

#include <string>
#include <optional>
#include <cstdint>

namespace gta5opt::adapters {

std::optional<uint32_t> find_process_by_name(const std::string& name);
void* open_process_for_rw(uint32_t pid);
void  close_handle(void* handle);

std::optional<uintptr_t> module_base(uint32_t pid, const std::string& module);
std::optional<size_t>    module_size(uint32_t pid, const std::string& module);

bool read_memory(void* handle, uintptr_t addr, void* out, size_t size);
bool write_memory(void* handle, uintptr_t addr, const void* in, size_t size);

unsigned long last_error();

} // namespace gta5opt::adapters