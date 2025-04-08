#include "Monitor.h"
#include "UI.h"

#include <iostream>
#include <optional>
#include <string>

namespace Monitor {

namespace {

using Types::IdType;
using Types::ValueType;
using Types::Vital;
using Types::Vitals;

std::optional<Vital> findVital(const Vitals& vitals, const IdType id)
{
    if (const auto it = vitals.find(id); it != vitals.end())
    {
        return it->second;
    }
    return std::nullopt;
}

[[nodiscard]] std::string status(const Vital& vital, const ValueType value)
{
    return vital.range.contains(value) ? "OK" : vital.errorMessage;
}
} // namespace

int launch(const Vitals& vitals, UI& ui)
{
    while (true)
    {
        const auto id = ui.getId();
        if (!id) break;

        const auto value = ui.getValue();
        if (!value) break;

        const auto vital = findVital(vitals, *id);
        if (!vital) continue;

        ui.report(status(*vital, *value));
    }
    return 0;
}

} // namespace Monitor
