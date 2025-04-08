// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#pragma once

#include "Types.h"

#include <filesystem>

namespace Config {

[[nodiscard]] Types::Vitals load(const std::filesystem::path& path);

} // namespace Config
