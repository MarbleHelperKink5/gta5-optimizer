#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

namespace gta5opt::services {

struct Signature {
    std::string module;
    std::string pattern;
    int offset = 0;
};

class SignatureService {
public:
    explicit SignatureService(const std::string& ini_path);

    bool load();
    const Signature* find(const std::string& name) const;

private:
    std::string ini_path_;
    std::unordered_map<std::string, Signature> table_;
};

} // namespace gta5opt::services