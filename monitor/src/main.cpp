// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "Config.h"
#include "ConsoleUI.h"
#include "Monitor.h"
#include "Print.h"

#include <CLI/CLI.hpp>

#include <format>
#include <iostream>
#include <string>

int main(const int argc, char* argv[])
{
    auto app        = CLI::App{"Monitor Application", "Monitor"};
    argv            = app.ensure_utf8(argv);
    auto configPath = std::string{"config.yml"};
    app.add_option("-c,--config", configPath, "config file path");
    CLI11_PARSE(app, argc, argv);

    const auto vitals = Config::load(configPath);
    std::cout << std::format("Configuration from {}:\n{}", configPath, toString(vitals));

    auto consoleUI = ConsoleUI{};
    return Monitor::launch(vitals, consoleUI);
}
