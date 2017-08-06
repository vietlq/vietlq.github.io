#include <gtest/gtest.h>
#include <iostream>

const float FLOAT_UPPER = 0.2000000f;
const float FLOAT_MID2  = 0.1999999f;
const float FLOAT_MID   = 0.1999990f;
const float FLOAT_LOWER = 0.1999980f;

TEST(NearlyEqual, SixDecimalPlaces1)
{
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID, 1e-6f);
}

TEST(NearlyEqual, SixDecimalPlaces2)
{
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID);
}

TEST(NearlyEqual, SixDecimalPlaces3)
{
    EXPECT_NEAR(FLOAT_LOWER, FLOAT_MID, 1e-6f);
}

TEST(NearlyEqual, SixDecimalPlaces4)
{
    EXPECT_FLOAT_EQ(FLOAT_LOWER, FLOAT_MID);
}

TEST(NearlyEqual, SevenDecimalPlaces1)
{
    EXPECT_NEAR(FLOAT_UPPER, FLOAT_MID2, 1e-7f);
}

TEST(NearlyEqual, SevenDecimalPlaces2)
{
    EXPECT_FLOAT_EQ(FLOAT_UPPER, FLOAT_MID2);
}
