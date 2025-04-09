// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#pragma once

#include "Types.h"

#include <map>
#include <optional>

class UI
{
  public:
    using Readings = std::map<Types::IdType, Types::ValueType>;
    struct Status
    {
        bool        ok;
        std::string message;
    };

    [[nodiscard]] virtual std::optional<Readings> getReadings() const          = 0;
    virtual void                                  report(const Status& status) = 0;

    virtual ~UI()            = default;
    UI(const UI&)            = delete;
    UI(UI&&)                 = delete;
    UI& operator=(const UI&) = delete;
    UI& operator=(UI&&)      = delete;

  protected:
    UI() = default;
};
