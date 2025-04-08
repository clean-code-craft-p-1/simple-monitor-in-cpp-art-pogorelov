// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#pragma once

#include "Types.h"

#include <string>

[[nodiscard]] std::string   toString(const Types::Vitals& vitals);
[[nodiscard]] std::string   toString(const Types::Vital& vital);
