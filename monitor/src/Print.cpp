// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "Print.h"

#include <format>
#include <numeric>
#include <string>

namespace {
constexpr auto kLineFormat = "{:>3} | {:>6} | {:>6} | {:20} | {:>12} | {:>12}\n";
} // namespace

std::string toString(const Types::Vitals& vitals)
{
    const auto header =
        std::format(kLineFormat, "ID", "Min", "Max", "Name", "Low Warning", "High Warning");
    return std::accumulate(vitals.begin(), vitals.end(), header, [](auto&& acc, const auto& vital) {
        return std::format("{}{}", acc, toString(vital.second));
    });
}

std::string toString(const Types::Vital& vital)
{
    const auto& [id, range, name, errorMessage, warning] = vital;
    const auto toString    = [](const auto& value) { return std::format("{}", value); };
    const auto lowWarning  = warning ? toString(warning->min) : "N/A";
    const auto highWarning = warning ? toString(warning->max) : "N/A";
    return std::format(
        kLineFormat, vital.id, range.min, range.max, vital.name, lowWarning, highWarning);
}
