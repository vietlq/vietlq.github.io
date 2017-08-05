+++
draft = true
thumbnail = ""
tags = []
categories = []
date = "2017-08-05T15:54:55+01:00"
title = "Float Double In Simple Words"
description = ""
+++

```
#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return (std::abs(x-y) < (
        std::numeric_limits<T>::epsilon() *
            (std::abs(x) + std::abs(y)) * ulp))
    // unless the result is subnormal
           || (std::abs(x-y) < std::numeric_limits<T>::min());
}
int main()
{
    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);

    std::cout << "std::numeric_limits<float>::min() = "
        << std::numeric_limits<float>::min() << std::endl;
    std::cout << "std::numeric_limits<float>::epsilon() = "
        << std::numeric_limits<float>::epsilon() << std::endl;

    std::cout << "std::numeric_limits<double>::min() = "
        << std::numeric_limits<double>::min() << std::endl;
    std::cout << "std::numeric_limits<double>::epsilon() = "
        << std::numeric_limits<double>::epsilon() << std::endl;

    if(d1 == d2) {
        std::cout << "d1 == d2\n";
    }
    else {
        std::cout << "d1 != d2\n";
    }

    for (int ulp = 0; ulp < 6; ++ulp) {
        std::cout << "ulp = " << ulp << std::endl;

        if(almost_equal(d1, d2, ulp)) {
            std::cout << "d1 almost equals d2\n";
        }
        else {
            std::cout << "d1 does not almost equal d2\n";
        }
    }

    int num1 = 0x42f6e9d7;
    int num2 = 0x42f6e9d4;
    const float* f1 = reinterpret_cast<float*>(&num1);
    const float* f2 = reinterpret_cast<float*>(&num2);
    const float& float1 = *f1;
    const float& float2 = *f2;

    std::cout << "num1 = " << num1 << std::endl;
    std::cout << "num2 = " << num2 << std::endl;

    std::cout << "float1 = " << float1 << std::endl;
    std::cout << "float2 = " << float2 << std::endl;
    std::cout << "(float1 == float2) = " << (float1 == float2) << std::endl;
}
```