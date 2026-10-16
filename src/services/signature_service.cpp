#include "services/signature_service.hpp"
#include "utils/logger.hpp"

#include <fstream>
#include <sstream>

namespace gta5opt::services {

SignatureService::SignatureService(const std::string& ini_path) : ini_path_(ini_path) {}

bool SignatureService::load() {
    std::ifstream in(ini_path_);
    if (!in) {
        LOG_ERROR("signature file not found: {}", ini_path_);
        return false;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == ';' || line[0] == '[') continue;
        auto eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string name = line.substr(0, eq);
        std::string rest = line.substr(eq + 1);
        auto bang = rest.find('!');
        auto semi = rest.rfind(';');
        if (bang == std::string::npos) continue;

        Signature sig;
        std::string body = rest.substr(bang + 1, semi == std::string::npos ? std::string::npos : semi - bang - 1);
        auto q1 = body.find('"');
        auto q2 = body.rfind('"');
        if (q1 != std::string::npos && q2 != q1) {
            sig.module = rest.substr(0, bang);
            sig.pattern = body.substr(q1 + 1, q2 - q1 - 1);
        }
        if (semi != std::string::npos) {
            try { sig.offset = std::stoi(rest.substr(semi + 1)); } catch (...) { sig.offset = 0; }
        }
        table_[name] = std::move(sig);
    }

    LOG_INFO("loaded {} signatures", table_.size());
    return !table_.empty();
}

const Signature* SignatureService::find(const std::string& name) const {
    auto it = table_.find(name);
    return it == table_.end() ? nullptr : &it->second;
}

} // namespace gta5opt::services