#include "Monitor.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace Monitor {

namespace {

using namespace Types;

constexpr auto kOK                    = "OK";
constexpr auto kIdMessage             = "Enter ID (or type 'exit' to quit):\n> ";
constexpr auto kValueMessage          = "Enter value (or type 'exit' to quit):\n> ";
constexpr auto kIdErrorMessage        = "Invalid ID\n";
constexpr auto kValueErrorMessage     = "Invalid value\n";
constexpr auto kIdUnknownErrorMessage = "Unknown ID\n";

std::optional<Vital> findVital(const Vitals& vitals, const IdType id)
{
    if (const auto it = vitals.find(id); it != vitals.end())
    {
        return it->second;
    }
    std::cout << kIdUnknownErrorMessage;
    return std::nullopt;
}

template <typename T>
std::optional<T> tryParse(const std::string& input)
{
    std::istringstream iss(input);
    if (T value; iss >> value) return value;
    return std::nullopt;
}

template <typename T>
std::optional<T> prompt(const std::string& message, const std::string& errorMessage)
{
    while (true)
    {
        std::cout << message;
        std::string input;
        if (!std::getline(std::cin, input))
        {
            std::cout << errorMessage;
            continue;
        }

        if (input == "exit") return std::nullopt;

        const auto value = tryParse<T>(input);
        if (!value)
        {
            std::cout << errorMessage;
            continue;
        }
        return *value;
    }
}

} // namespace

int launch(const Vitals& vitals)
{
    while (true)
    {
        const auto id = prompt<IdType>(kIdMessage, kIdErrorMessage);
        if (!id) break;

        const auto vital = findVital(vitals, *id);
        if (!vital) continue;

        const auto value = prompt<ValueType>(kValueMessage, kValueErrorMessage);
        if (!value) break;

        const auto status = vital->range.contains(*value) ? kOK : vital->errorMessage;
        std::cout << status << "\n";
    }
    return 0;
}

} // namespace Monitor
