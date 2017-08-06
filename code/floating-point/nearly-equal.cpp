#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>

////////////////////////////////////////////////////////////////
// Types and constants
////////////////////////////////////////////////////////////////

const float FLOAT_UPPER      = 0.2000000f;
const float FLOAT_MID2       = 0.1999999f;
const float FLOAT_MID        = 0.1999990f;
const float FLOAT_LOWER      = 0.1999980f;
const float FLOAT_MAX_DIFF6  = 1e-6f;
const float FLOAT_MAX_DIFF7  = 1e-7f;
// Note that 1e-7f is smaller than machine epsilon for floats.
// So one cannot naively use 1e-7f as difference between 2 floats.
// Machine epsilon for float (32b) = 2.**-23 = 1.1920928955078125e-07
const float FLOAT_EPSILON  = std::numeric_limits<float>::epsilon();

using Float32 = ::testing::internal::FloatingPoint<float>;
using Float64 = ::testing::internal::FloatingPoint<double>;

////////////////////////////////////////////////////////////////
// Utility functions
////////////////////////////////////////////////////////////////

inline Float32::Bits dist_ulp(const Float32& f1, const Float32& f2)
{
    return Float32::getUlpDistance(f1, f2);
}

inline Float32::Bits dist_ulp(float fv1, float fv2)
{
    const Float32 f1(fv1);
    const Float32 f2(fv2);
    return dist_ulp(f1, f2);
}

Float32::Bits exponent_bits(float fv)
{
    const Float32 f(fv);
    const Float32::Bits biased_bits = (f.exponent_bits() >> Float32::kFractionBitCount);
    const long unbiased_bits = long(biased_bits) - 127;
    std::cout << "exponent_bits for " << fv << std::endl;
    std::cout << "biased_bits = " << biased_bits << std::endl;
    std::cout << "unbiased_bits = " << unbiased_bits << std::endl;
    return biased_bits;
}

void report_ulp(float fv1, float fv2)
{
    const Float32 f1(fv1);
    const Float32 f2(fv2);
    std::cout << std::setprecision(20) << std::endl;
    exponent_bits(fv1);
    exponent_bits(fv2);
    std::cout << "ULP distance = " << Float32::getUlpDistance(f1, f2)
        << " for " << fv1
        << " and " << fv2 << std::endl;
}

bool nearlyEqualRelative(
        float fv1, float fv2, float absDiff, float relDiff = 0.0f)
{
    // Forget about NaN
    if (std::isnan(fv1) || std::isnan(fv2))
    {
        return false;
    }

    // Works for Infinities as well
    if (fv1 == fv2)
    {
        return true;
    }

    const float diff = std::abs(fv1 - fv2);
    const float absA = std::abs(fv1);
    const float absB = std::abs(fv2);
    const float maxVal = std::max(absA, absB);

    if (maxVal < FLOAT_EPSILON)
    {
        return diff/(absA + absB) < relDiff;
    }
    else
    {
        if (diff < absDiff)
        {
            return true;
        }

        return diff/(absA + absB) < relDiff;
    }
}

////////////////////////////////////////////////////////////////
// Test cases
////////////////////////////////////////////////////////////////

TEST(NearlyEqual, Float6AbsUpperMid)
{
    const float diff = std::abs(FLOAT_UPPER - FLOAT_MID);
    std::cout << "Float6AbsUpperMid: diff = " << diff << std::endl;
    EXPECT_TRUE(diff < FLOAT_MAX_DIFF6) << "diff = " << diff
        << " is greater than FLOAT_MAX_DIFF6 = " << FLOAT_MAX_DIFF6;
}

TEST(NearlyEqual, Double6AbsUpperMid)
{
    // Look at the source code and see that EXPECT_NEAR is using double
    // https://github.com/google/googletest/blob/078d5d930ad8b25b3c61556dc6de7ad13fa9a179/googletest/include/gtest/gtest.h#L2043
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID, FLOAT_MAX_DIFF6);
}

TEST(NearlyEqual, Float6UlpUpperMid)
{
    report_ulp(FLOAT_UPPER, FLOAT_MID);
    //EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID);
    EXPECT_TRUE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID, FLOAT_MAX_DIFF6));
    EXPECT_TRUE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID, FLOAT_MAX_DIFF6, 0.001));
}

TEST(NearlyEqual, Float6AbsLowerMid)
{
    const float diff = std::abs(FLOAT_LOWER - FLOAT_MID);
    std::cout << "Float6AbsLowerMid : diff = " << diff << std::endl;
    EXPECT_TRUE(diff < FLOAT_MAX_DIFF6) << "diff = " << diff
        << " is greater than FLOAT_MAX_DIFF6 = " << FLOAT_MAX_DIFF6;
}

TEST(NearlyEqual, Double6AbsLowerMid)
{
    // Look at the source code and see that EXPECT_NEAR is using double
    // https://github.com/google/googletest/blob/078d5d930ad8b25b3c61556dc6de7ad13fa9a179/googletest/include/gtest/gtest.h#L2043
    EXPECT_NEAR(FLOAT_LOWER, FLOAT_MID, FLOAT_MAX_DIFF6);
}

TEST(NearlyEqual, Float6UlpLowerMid)
{
    report_ulp(FLOAT_LOWER, FLOAT_MID);
    //EXPECT_FLOAT_EQ(FLOAT_LOWER, FLOAT_MID);
    EXPECT_TRUE(nearlyEqualRelative(FLOAT_LOWER, FLOAT_MID, FLOAT_MAX_DIFF6));
    EXPECT_TRUE(nearlyEqualRelative(FLOAT_LOWER, FLOAT_MID, FLOAT_MAX_DIFF6, 0.001));
}

TEST(NearlyEqual, Float7AbsUpperMid2)
{
    const float diff = std::abs(FLOAT_UPPER - FLOAT_MID2);
    std::cout << "Float7AbsUpperMid2: diff = " << diff << std::endl;
    EXPECT_FALSE(diff < FLOAT_MAX_DIFF7);
    EXPECT_FALSE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7));
    EXPECT_TRUE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7, 0.001));
}

TEST(NearlyEqual, Double7AbsUpperMid2)
{
    // Look at the source code and see that EXPECT_NEAR is using double
    // https://github.com/google/googletest/blob/078d5d930ad8b25b3c61556dc6de7ad13fa9a179/googletest/include/gtest/gtest.h#L2043
    //EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7);
    EXPECT_FALSE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7));
    EXPECT_TRUE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7, 0.001));
}

TEST(NearlyEqual, Float7UlpUpperMid2)
{
    report_ulp(FLOAT_UPPER, FLOAT_MID2);
    //EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID2);
    EXPECT_FALSE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7));
    EXPECT_TRUE(nearlyEqualRelative(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7, 0.001));
}
