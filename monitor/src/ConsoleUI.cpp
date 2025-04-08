// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "ConsoleUI.h"
#include "Types.h"

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

template <typename T>
std::optional<T> tryParse(const std::string& input)
{
    std::istringstream iss(input);
    char               leftover{};
    if (T value; iss >> value && !(iss >> leftover)) return value;
    return std::nullopt;
}

template <typename T>
std::optional<T> prompt(const std::string& message, const std::string& errorMessage)
{
    while (true)
    {
        std::cout << message;

        std::string input;
        if (!std::getline(std::cin, input) || input == "exit")
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
} // namespace

std::optional<IdType> ConsoleUI::getId() const
{
    return prompt<IdType>(kIdMessage, kIdErrorMessage);
}

std::optional<ValueType> ConsoleUI::getValue() const
{
    return prompt<ValueType>(kValueMessage, kValueErrorMessage);
}

void ConsoleUI::report(const std::string& status)
{
    std::cout << status << "\n";
}
