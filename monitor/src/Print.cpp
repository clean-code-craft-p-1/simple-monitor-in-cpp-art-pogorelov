// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "Print.h"

#include <format>
#include <numeric>

namespace {
constexpr auto kLineFormat = "{:>3} | {:>6} | {:>6} | {:20}\n";
} // namespace

std::string toString(const Types::Vitals& vitals)
{
    const auto header = std::format(kLineFormat, "ID", "Min", "Max", "Name");
    return std::accumulate(vitals.begin(), vitals.end(), header, [](auto&& acc, const auto& vital) {
        return std::format("{}{}", acc, toString(vital.second));
    });
}

std::string toString(const Types::Vital& vital)
{
    const auto& [id, range, name, errorMessage] = vital;
    return std::format(kLineFormat, id, range.min, range.max, name);
}
