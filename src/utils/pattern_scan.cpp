#include "utils/pattern_scan.hpp"
#include "adapters/win32_process_adapter.hpp"

#include <vector>
#include <sstream>

namespace gta5opt::utils {

namespace {
    struct ByteMask { int value; bool wildcard; };

    std::vector<ByteMask> parse(const std::string& pattern) {
        std::vector<ByteMask> out;
        std::istringstream ss(pattern);
        std::string tok;
        while (ss >> tok) {
            if (tok == "??") out.push_back({0, true});
            else out.push_back({std::stoi(tok, nullptr, 16), false});
        }
        return out;
    }
}

std::optional<uintptr_t> scan_pattern(void* process_handle,
                                      uintptr_t base,
                                      size_t size,
                                      const std::string& pattern) {
    auto mask = parse(pattern);
    if (mask.empty()) return std::nullopt;

    constexpr size_t kChunk = 0x1000;
    std::vector<uint8_t> buf(kChunk + mask.size());

    for (uintptr_t off = 0; off + mask.size() < size; off += kChunk) {
        size_t to_read = std::min(kChunk + mask.size(), size - off);
        if (!adapters::read_memory(process_handle, base + off, buf.data(), to_read)) continue;

        for (size_t i = 0; i + mask.size() <= to_read; ++i) {
            bool hit = true;
            for (size_t j = 0; j < mask.size(); ++j) {
                if (mask[j].wildcard) continue;
                if (buf[i + j] != static_cast<uint8_t>(mask[j].value)) { hit = false; break; }
            }
            if (hit) return base + off + i;
        }
    }
    return std::nullopt;
}

} // namespace gta5opt::utils