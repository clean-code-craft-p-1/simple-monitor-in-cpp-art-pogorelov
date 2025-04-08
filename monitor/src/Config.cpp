// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "Config.h"

#include <string>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

namespace Config {

Types::Vitals load(const std::filesystem::path& path)
{
    using namespace Types;
    Vitals vitals;
    for (const auto& node : YAML::LoadFile(path.string()))
    {
        const auto& data         = node.second;
        const auto& min          = data["min"];
        const auto& max          = data["max"];
        const auto  id           = data["id"].as<IdType>();
        const auto  name         = data["name"].as<std::string>();
        const auto  errorMessage = data["errorMessage"].as<std::string>();

        vitals.try_emplace(id,
                           Vital{.id           = id,
                                 .range        = Range{min.as<ValueType>(), max.as<ValueType>()},
                                 .name         = name,
                                 .errorMessage = errorMessage});
    }
    return vitals;
}

} // namespace Config
