// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

/**
 * For simplicity and to save time, I'm skipping this test.
 * The important thing is that this functionality can be tested in isolation,
 * independently of the other components.
 *
 * Thanks to dependency injection, we can easily replace the actual UI with mock object
 * and provide the necessary Vitals data for testing.
 */

#include <Monitor.h>
#include <UI.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Monitor::Test {
namespace {

using ::testing::AllOf;
using ::testing::Field;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrEq;
using Types::Vital;
using Types::Vitals;
using Readings = UI::Readings;
using Status   = UI::Status;
using enum UI::Status::Type;

struct UIMock : public UI
{
    MOCK_METHOD(std::optional<Readings>, getReadings, (), (const));
    MOCK_METHOD(void, report, (const Status& status), ());
};

constexpr auto kId           = 1;
constexpr auto kErrorMessage = "Out of range";
constexpr auto kLowMessage   = "Low";
constexpr auto kHighMessage  = "High";
const auto     kVital        = Vital{.id           = kId,
                                     .range        = {.min = 0, .max = 100},
                                     .errorMessage = kErrorMessage,
                                     .warning      = std::nullopt};

const auto kVitalWithWarning = Vital{.id           = kId,
                                     .range        = {.min = 0, .max = 100},
                                     .errorMessage = kErrorMessage,
                                     .warning      = Vital::Warning{
                                              .min  = 10,
                                              .max  = 90,
                                              .low  = kLowMessage,
                                              .high = kHighMessage,
                                     }};
} // namespace

struct MonitorTest : public ::testing::Test
{
    NiceMock<UIMock> ui;

    void launch(const Vitals& vitals, const Readings& readings)
    {
        EXPECT_CALL(ui, getReadings())
            .Times(2)
            .WillOnce(Return(readings))
            .WillOnce(Return(std::nullopt));
        EXPECT_EQ(Monitor::launch(vitals, ui), 0);
    }
};

TEST_F(MonitorTest, givenNoReadingsMonitorShouldExit)
{
    const auto vitals = Vitals{{kId, kVital}};
    EXPECT_CALL(ui, getReadings()).WillOnce(Return(std::nullopt));
    EXPECT_EQ(Monitor::launch(vitals, ui), 0);
}

TEST_F(MonitorTest, givenIncorrectReadingsMonitorShouldRequestAgain)
{
    const auto vitals   = Vitals{{kId, kVital}};
    const auto readings = Readings{{kId + 1, 0}};
    launch(vitals, readings);
}

TEST_F(MonitorTest, givenReadingsInRangeMonitorShouldReportOk)
{
    EXPECT_CALL(ui, report(Field(&Status::type, Ok))).Times(1);

    const auto vitals   = Vitals{{kId, kVital}};
    const auto readings = Readings{{kId, 50}};
    launch(vitals, readings);
}

TEST_F(MonitorTest, givenReadingsNotInRangeMonitorShouldReportError)
{
    EXPECT_CALL(
        ui,
        report(AllOf(Field(&Status::type, Error), Field(&Status::message, StrEq(kErrorMessage)))))
        .Times(1);

    const auto vitals   = Vitals{{kId, kVital}};
    const auto readings = Readings{{kId, 150}};
    launch(vitals, readings);
}

TEST_F(MonitorTest, givenWarningDisabledAndLowReadingsMonitorShouldReportOk)
{
    EXPECT_CALL(ui, report(Field(&Status::type, Ok))).Times(1);

    const auto vitals   = Vitals{{kId, kVital}};
    const auto readings = Readings{{kId, 5}};
    launch(vitals, readings);
}

TEST_F(MonitorTest, givenWarningDisabledAndHighReadingsMonitorShouldReportOk)
{
    EXPECT_CALL(ui, report(Field(&Status::type, Ok))).Times(1);

    const auto vitals   = Vitals{{kId, kVital}};
    const auto readings = Readings{{kId, 95}};
    launch(vitals, readings);
}

TEST_F(MonitorTest, givenWarningEnabledAndLowReadingsMonitorShouldReportWarning)
{
    EXPECT_CALL(
        ui,
        report(AllOf(Field(&Status::type, Warning), Field(&Status::message, StrEq(kLowMessage)))))
        .Times(1);

    const auto vitals   = Vitals{{kId, kVitalWithWarning}};
    const auto readings = Readings{{kId, 5}};
    launch(vitals, readings);
}

TEST_F(MonitorTest, givenWarningEnabledAndHighReadingsMonitorShouldReportWarning)
{
    EXPECT_CALL(
        ui,
        report(AllOf(Field(&Status::type, Warning), Field(&Status::message, StrEq(kHighMessage)))))
        .Times(1);

    const auto vitals   = Vitals{{kId, kVitalWithWarning}};
    const auto readings = Readings{{kId, 95}};
    launch(vitals, readings);
}
} // namespace Monitor::Test
