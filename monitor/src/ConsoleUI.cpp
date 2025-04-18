// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "ConsoleUI.h"
#include "Types.h"

#include <format>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace {

using Types::IdType;
using Types::ValueType;
using Types::Vital;
using Types::Vitals;

constexpr auto kIdMessage         = "Enter ID (or type 'exit' to quit):\n> ";
constexpr auto kValueMessage      = "Enter value (or type 'exit' to quit):\n> ";
constexpr auto kIdErrorMessage    = "Invalid ID\n";
constexpr auto kValueErrorMessage = "Invalid value\n";
constexpr auto kRed               = "\033[0;31m";
constexpr auto kGreen             = "\033[1;32m";
constexpr auto kYellow            = "\033[1;33m";
constexpr auto kReset             = "\033[0m";

template <typename T>
std::optional<T> tryParse(const std::string& input)
{
    std::istringstream iss(input);
    char               leftover{};
    if (T value; iss >> value && !(iss >> leftover)) return value;
    return std::nullopt;
}

std::string readLine()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool exitRequested(const std::string& input)
{
    return input == "exit";
}

template <typename T>
std::optional<T> prompt(const std::string& message, const std::string& errorMessage)
{
    while (true)
    {
        std::cout << message;

        const auto input = readLine();
        if (exitRequested(input))
        {
            return std::nullopt;
        }
        if (const auto value = tryParse<T>(input))
        {
            return *value;
        }

        std::cout << errorMessage;
    }
}

std::optional<IdType> getId()
{
    return prompt<IdType>(kIdMessage, kIdErrorMessage);
}

std::optional<ValueType> getValue()
{
    return prompt<ValueType>(kValueMessage, kValueErrorMessage);
}

std::string color(const UI::Status::Type type)
{
    using enum UI::Status::Type;
    switch (type)
    {
        case Ok:
            return kGreen;
        case Warning:
            return kYellow;
        case Error:
            return kRed;
        default:
            return kReset;
    }
}
} // namespace

std::optional<ConsoleUI::Readings> ConsoleUI::getReadings() const
{
    const auto id = getId();
    if (!id) return std::nullopt;

    const auto value = getValue();
    if (!value) return std::nullopt;

    return Readings{{*id, *value}};
}

void ConsoleUI::report(const Status& status)
{
    const auto& [type, message] = status;
    std::cout << std::format("{}{}{}\n", color(type), message, kReset);
}
