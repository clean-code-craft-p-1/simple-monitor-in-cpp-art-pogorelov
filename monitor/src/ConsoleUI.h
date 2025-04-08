// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#pragma once

#include "Types.h"
#include "UI.h"

#include <optional>
#include <string>

class ConsoleUI final : public UI
{
  public:
    // From UI
    [[nodiscard]] std::optional<Types::IdType>    getId() const override;
    [[nodiscard]] std::optional<Types::ValueType> getValue() const override;
    void                                          report(const std::string& status) override;

    ConsoleUI()                            = default;
    ~ConsoleUI() override                  = default;
    ConsoleUI(const ConsoleUI&)            = delete;
    ConsoleUI(ConsoleUI&&)                 = delete;
    ConsoleUI& operator=(const ConsoleUI&) = delete;
    ConsoleUI& operator=(ConsoleUI&&)      = delete;
};
