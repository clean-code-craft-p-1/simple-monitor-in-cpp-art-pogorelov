// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "Config.h"
#include "ConsoleUI.h"
#include "Monitor.h"
#include "Print.h"

#include <CLI/CLI.hpp>

#include <exception>
#include <format>
#include <iostream>
#include <string>

int main(const int argc, char* argv[])
try
{
    auto app        = CLI::App{"Monitor Application"};
    argv            = app.ensure_utf8(argv);
    auto configPath = std::string{"config.yml"};
    auto locale     = std::string{"en"};
    app.add_option("-c,--config", configPath, "config file path");
    app.add_option("-l,--locale", locale, "locale code");
    CLI11_PARSE(app, argc, argv);

    const auto vitals = Config::load(configPath, locale);
    std::cout << std::format(
        "Configuration from \"{}\", locale \"{}\":\n{}", configPath, locale, toString(vitals));

    auto consoleUI = ConsoleUI{};
    return Monitor::launch(vitals, consoleUI);
}
catch (const std::exception& error)
{
    std::cerr << error.what();
    return -1;
}
