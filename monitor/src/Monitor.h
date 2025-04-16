#pragma once

#include "Types.h"
#include "UI.h"

namespace Monitor {

[[nodiscard]] int launch(const Types::Vitals& vitals, UI& ui);

} // namespace Monitor
