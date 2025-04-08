// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#pragma once

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <variant>

namespace Types {

using IdType    = std::uint16_t;
using ValueType = double;

template <typename T>
struct Range
{
    using value_type = T;
    T min;
    T max;

    [[nodiscard]] bool contains(const T value) const noexcept
    {
        return value >= min && value <= max;
    }
};

struct Vital
{
    IdType           id;
    Range<ValueType> range;
    std::string      name;
    std::string      errorMessage;
};

class Vitals : public std::map<IdType, Vital>
{
  public:
    std::optional<Vital> getVital(const IdType id) const noexcept
    {
        if (const auto it = find(id); it != end())
        {
            return it->second;
        }
        return std::nullopt;
    }
};
} // namespace Types
