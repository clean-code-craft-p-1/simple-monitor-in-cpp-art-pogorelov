// Copyright(c), Philips Medical Systems Nederland B.V., IGT-Devices

#include "Types.h"

#include <gtest/gtest.h>
#include <rapidcheck.h>

namespace Types::Test {

TEST(Range, GivenValueLessThanMinContainsShouldReturnFalse)
{
    rc::check("Given value < min, contains should return false", [] {
        const auto min   = *rc::gen::arbitrary<ValueType>();
        const auto max   = *rc::gen::suchThat<ValueType>([min](const auto x) { return x >= min; });
        const auto value = *rc::gen::suchThat<ValueType>([min](const auto x) { return x < min; });

        const auto range = Range{min, max};
        RC_ASSERT(!range.contains(value));
    });
}

TEST(Range, GivenValueGreaterThanMaxContainsShouldReturnFalse)
{
    rc::check("Given value > max, contains should return false", [] {
        const auto min   = *rc::gen::arbitrary<ValueType>();
        const auto max   = *rc::gen::suchThat<ValueType>([min](const auto x) { return x >= min; });
        const auto value = *rc::gen::suchThat<ValueType>([max](const auto x) { return x > max; });

        const auto range = Range{min, max};
        RC_ASSERT(!range.contains(value));
    });
}

TEST(Range, GivenValueInRangeContainsShouldReturnTrue)
{
    rc::check("Given value in range, contains should return true", [] {
        const auto min   = *rc::gen::arbitrary<ValueType>();
        const auto max   = *rc::gen::suchThat<ValueType>([min](const auto x) { return x >= min; });
        const auto value = *rc::gen::suchThat<ValueType>(
            [min, max](const auto x) { return x >= min && x <= max; });

        const auto range = Range{min, max};
        RC_ASSERT(range.contains(value));
    });
}

} // namespace Types::Test
