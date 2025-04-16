// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "Config.h"
#include "Types.h"

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <optional>
#include <string>

namespace Config {

using Types::IdType;
using Types::Range;
using Types::ValueType;
using Types::Vital;
using Types::Vitals;
using Warning = Vital::Warning;

namespace {
std::string localized(const YAML::Node& root, const std::string& key, const std::string& locale)
{
    const auto& node = root[key];
    if (node[locale]) return node[locale].as<std::string>();
    return node["en"].as<std::string>();
}

std::optional<Warning>
tryParseWarning(const YAML::Node& data, const Range<ValueType>& range, const std::string& locale)
{
    const auto& warning = data["warning"];
    if (!warning || !warning["enabled"].as<bool>()) return std::nullopt;

    const auto tolerance = warning["tolerance"].as<double>();
    const auto low       = localized(warning, "low_warning", locale);
    const auto high      = localized(warning, "high_warning", locale);
    const auto delta     = range.max * tolerance / 100.0;

    return Warning{
        .min  = range.min + delta,
        .max  = range.max - delta,
        .low  = low,
        .high = high,
    };
}
} // namespace

Vitals load(const std::filesystem::path& path, const std::string& locale)
{
    Vitals vitals;
    for (const auto& node : YAML::LoadFile(path.string()))
    {
        const auto& data         = node.second;
        const auto  min          = data["min"].as<ValueType>();
        const auto  max          = data["max"].as<ValueType>();
        const auto  range        = Range{.min = min, .max = max};
        const auto  id           = data["id"].as<IdType>();
        const auto  name         = localized(data, "name", locale);
        const auto  errorMessage = localized(data, "error_message", locale);
        const auto  warning      = tryParseWarning(data, range, locale);

        vitals.try_emplace(id,
                           Vital{.id           = id,
                                 .range        = range,
                                 .name         = name,
                                 .errorMessage = errorMessage,
                                 .warning      = warning});
    }
    return vitals;
}

} // namespace Config
