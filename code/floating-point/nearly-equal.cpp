#include <gtest/gtest.h>
#include <iostream>

const float FLOAT_UPPER = 0.2000000f;
const float FLOAT_MID2  = 0.1999999f;
const float FLOAT_MID   = 0.1999990f;
const float FLOAT_LOWER = 0.1999980f;
const float FLOAT_EPS6  = 1e-6f;
const float FLOAT_EPS7  = 1e-7f;

TEST(NearlyEqual, Float6AbsUpperMid)
{
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID, FLOAT_EPS6);
}

TEST(NearlyEqual, Float6UlpUpperMid)
{
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID);
}

TEST(NearlyEqual, Float6AbsLowerMid)
{
    EXPECT_NEAR(FLOAT_LOWER, FLOAT_MID, FLOAT_EPS6);
}

TEST(NearlyEqual, Float6UlpLowerMid)
{
    EXPECT_FLOAT_EQ(FLOAT_LOWER, FLOAT_MID);
}

TEST(NearlyEqual, Float7AbsUpperMid2)
{
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID2, FLOAT_EPS7);
}

TEST(NearlyEqual, Float7UlpUpperMid2)
{
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID2);
}
