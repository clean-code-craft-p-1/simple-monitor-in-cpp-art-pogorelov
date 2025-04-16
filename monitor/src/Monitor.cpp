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

[[nodiscard]] UI::Status status(const Vital& vital, const ValueType value)
{
    const auto inRange = vital.range.contains(value);
    if (inRange && vital.warning)
    {
        if (value <= vital.warning->min)
        {
            return UI::Status{.ok = false, .message = vital.warning->low};
        }
        if (value >= vital.warning->max)
        {
            return UI::Status{.ok = false, .message = vital.warning->high};
        }
    }
    const auto message = inRange ? "OK" : vital.errorMessage;
    return UI::Status{.ok = inRange, .message = message};
}

void report(const Vitals& vitals, const UI::Readings& readings, UI& ui)
{
    for (const auto& [id, value] : readings)
    {
        const auto vital = findVital(vitals, id);
        if (!vital) continue;

        ui.report(status(*vital, value));
    }
}
} // namespace

int launch(const Vitals& vitals, UI& ui)
{
    while (true)
    {
        const auto readings = ui.getReadings();
        if (!readings) break;

        report(vitals, *readings, ui);
    }
    return 0;
}

} // namespace Monitor
