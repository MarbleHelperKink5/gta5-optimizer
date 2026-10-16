#pragma once

#include <string>
#include <memory>

namespace gta5opt::core {

struct BootstrapOptions {
    std::string process_name = "GTA5.exe";
    std::string profile = "performance";
    bool attach_overlay = true;
    bool verbose = false;
};

class Bootstrap {
public:
    explicit Bootstrap(BootstrapOptions opts);
    ~Bootstrap();

    bool initialize();
    int run();
    void shutdown();

private:
    BootstrapOptions opts_;
    bool initialized_ = false;
};

} // namespace gta5opt::core