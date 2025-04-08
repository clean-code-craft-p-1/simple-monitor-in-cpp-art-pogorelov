// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <variant>

namespace Types {

template <typename T>
struct Range;

struct Vital;

using IdType    = std::uint16_t;
using ValueType = double;
using Vitals    = std::map<IdType, Vital>;

template <typename T>
struct Range
{
    using value_type = T;
    T min;
    T max;

    [[nodiscard]] bool contains(const T value) const
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

} // namespace Types
