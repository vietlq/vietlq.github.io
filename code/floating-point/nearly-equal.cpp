#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

const float FLOAT_UPPER = 0.2000000f;
const float FLOAT_MID2  = 0.1999999f;
const float FLOAT_MID   = 0.1999990f;
const float FLOAT_LOWER = 0.1999980f;
const float FLOAT_EPS6  = 1e-6f;
const float FLOAT_EPS7  = 1e-7f;

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
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID2);
}
