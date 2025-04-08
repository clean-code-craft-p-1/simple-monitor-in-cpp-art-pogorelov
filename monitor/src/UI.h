// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#pragma once

#include "Types.h"

#include <optional>

class UI
{
  public:
    [[nodiscard]] virtual std::optional<Types::IdType>    getId() const                        = 0;
    [[nodiscard]] virtual std::optional<Types::ValueType> getValue() const                     = 0;
    virtual void                                          report(const std::string& status) = 0;

    virtual ~UI()               = default;
    UI(const UI&)            = delete;
    UI(UI&&)                 = delete;
    UI& operator=(const UI&) = delete;
    UI& operator=(UI&&)      = delete;

  protected:
    UI() = default;
};
