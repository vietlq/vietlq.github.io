#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

const float FLOAT_UPPER      = 0.2000000f;
const float FLOAT_MID2       = 0.1999999f;
const float FLOAT_MID        = 0.1999990f;
const float FLOAT_LOWER      = 0.1999980f;
const float FLOAT_MAX_DIFF6  = 1e-6f;
const float FLOAT_MAX_DIFF7  = 1e-7f;
// Note that 1e-7f is smaller than machine epsilon for floats.
// So one cannot naively use 1e-7f as difference between 2 floats.
// Machine epsilon for float (32b) = 2.**-23 = 1.1920928955078125e-07
//const float FLOAT_EPSILON  = std::numeric_limits<float>::epsilon();

using Float32 = ::testing::internal::FloatingPoint<float>;
using Float64 = ::testing::internal::FloatingPoint<double>;

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
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID);
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
    EXPECT_FLOAT_EQ(FLOAT_LOWER, FLOAT_MID);
}

TEST(NearlyEqual, Float7AbsUpperMid2)
{
    const float diff = std::abs(FLOAT_UPPER - FLOAT_MID2);
    std::cout << "Float7AbsUpperMid2: diff = " << diff << std::endl;
    EXPECT_TRUE(diff < FLOAT_MAX_DIFF7) << "diff = " << diff
        << " is greater than FLOAT_MAX_DIFF7 = " << FLOAT_MAX_DIFF7;
}

TEST(NearlyEqual, Double7AbsUpperMid2)
{
    // Look at the source code and see that EXPECT_NEAR is using double
    // https://github.com/google/googletest/blob/078d5d930ad8b25b3c61556dc6de7ad13fa9a179/googletest/include/gtest/gtest.h#L2043
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID2, FLOAT_MAX_DIFF7);
}

TEST(NearlyEqual, Float7UlpUpperMid2)
{
    report_ulp(FLOAT_UPPER, FLOAT_MID2);
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID2);
}
