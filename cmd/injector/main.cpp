#include "core/bootstrap.hpp"
#include "utils/logger.hpp"

#include <cstdio>
#include <string>

int main(int argc, char** argv) {
    gta5opt::core::BootstrapOptions opts;
    opts.process_name = "GTA5.exe";
    opts.profile = "performance";
    opts.verbose = false;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--profile" && i + 1 < argc) opts.profile = argv[++i];
        else if (a == "--process" && i + 1 < argc) opts.process_name = argv[++i];
        else if (a == "--verbose") opts.verbose = true;
    }

    gta5opt::core::Bootstrap boot(opts);
    if (!boot.initialize()) {
        std::fprintf(stderr, "gta5-optimizer: init failed\n");
        return 1;
    }
    return boot.run();
}