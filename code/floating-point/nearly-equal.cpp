#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include <iostream>
#include <cmath>
#include <limits>

const float FLOAT_UPPER = 0.2000000f;
const float FLOAT_MID2  = 0.1999999f;
const float FLOAT_MID   = 0.1999990f;
const float FLOAT_LOWER = 0.1999980f;
const float FLOAT_EPS6  = 1e-6f;
// Note that 1e-7f is smaller than machine epsilon for floats.
// So one cannot reliable use 1e-7f for epsilon between 2 floats.
// One must use minimum epsilon = 2.**-23 = 1.1920928955078125e-07
// when comparing 2 floats
const float FLOAT_EPS7  = std::numeric_limits<float>::epsilon();

using Float32 = ::testing::internal::FloatingPoint<float>;
using Float64 = ::testing::internal::FloatingPoint<double>;

TEST(NearlyEqual, Float6AbsUpperMid)
{
    const float diff = std::abs(FLOAT_UPPER - FLOAT_MID);
    std::cout << "Float6AbsUpperMid: diff = " << diff << std::endl;
    EXPECT_TRUE(diff < FLOAT_EPS6) << "diff = " << diff
        << " is greater than FLOAT_EPS6 = " << FLOAT_EPS6;
}

TEST(NearlyEqual, Double6AbsUpperMid)
{
    // Look at the source code and see that EXPECT_NEAR is using double
    // https://github.com/google/googletest/blob/078d5d930ad8b25b3c61556dc6de7ad13fa9a179/googletest/include/gtest/gtest.h#L2043
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID, FLOAT_EPS6);
}

TEST(NearlyEqual, Float6UlpUpperMid)
{
    const Float32 f1(FLOAT_UPPER);
    const Float32 f2(FLOAT_MID);
    std::cout << "ULP distance = " << Float32::getUlpDistance(f1, f2)
        << " for " << FLOAT_UPPER
        << " and " << FLOAT_MID << std::endl;
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID);
}

TEST(NearlyEqual, Float6AbsLowerMid)
{
    const float diff = std::abs(FLOAT_LOWER - FLOAT_MID);
    std::cout << "Float6AbsLowerMid : diff = " << diff << std::endl;
    EXPECT_TRUE(diff < FLOAT_EPS6) << "diff = " << diff
        << " is greater than FLOAT_EPS6 = " << FLOAT_EPS6;
}

TEST(NearlyEqual, Double6AbsLowerMid)
{
    // Look at the source code and see that EXPECT_NEAR is using double
    // https://github.com/google/googletest/blob/078d5d930ad8b25b3c61556dc6de7ad13fa9a179/googletest/include/gtest/gtest.h#L2043
    EXPECT_NEAR(FLOAT_LOWER, FLOAT_MID, FLOAT_EPS6);
}

TEST(NearlyEqual, Float6UlpLowerMid)
{
    const Float32 f1(FLOAT_LOWER);
    const Float32 f2(FLOAT_MID);
    std::cout << "ULP distance = " << Float32::getUlpDistance(f1, f2)
        << " for " << FLOAT_LOWER
        << " and " << FLOAT_MID << std::endl;
    EXPECT_FLOAT_EQ(FLOAT_LOWER, FLOAT_MID);
}

TEST(NearlyEqual, Float7AbsUpperMid2)
{
    const float diff = std::abs(FLOAT_UPPER - FLOAT_MID2);
    std::cout << "Float7AbsUpperMid2: diff = " << diff << std::endl;
    EXPECT_TRUE(diff < FLOAT_EPS7) << "diff = " << diff
        << " is greater than FLOAT_EPS7 = " << FLOAT_EPS7;
}

TEST(NearlyEqual, Double7AbsUpperMid2)
{
    // Look at the source code and see that EXPECT_NEAR is using double
    // https://github.com/google/googletest/blob/078d5d930ad8b25b3c61556dc6de7ad13fa9a179/googletest/include/gtest/gtest.h#L2043
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID2, FLOAT_EPS7);
}

TEST(NearlyEqual, Float7UlpUpperMid2)
{
    const Float32 f1(FLOAT_UPPER);
    const Float32 f2(FLOAT_MID2);
    std::cout << "ULP distance = " << Float32::getUlpDistance(f1, f2)
        << " for " << FLOAT_UPPER
        << " and " << FLOAT_MID2 << std::endl;
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID2);
}
