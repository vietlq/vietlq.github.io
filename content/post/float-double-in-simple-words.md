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

void explore_ulp(int num1)
{
    const int num2 = num1 + 1;
    const float* f1 = reinterpret_cast<const float*>(&num1);
    const float* f2 = reinterpret_cast<const float*>(&num2);
    const float& float1 = *f1;
    const float& float2 = *f2;
    const float diff = std::abs(float1 - float2);
    const float float_epsilon = std::numeric_limits<float>::epsilon();

    std::cout << "num1 = " << num1 << std::endl;
    std::cout << "num2 = " << num2 << std::endl;

    std::cout << std::setprecision(20);

    std::cout << "float1 = " << float1 << std::endl;
    std::cout << "float2 = " << float2 << std::endl;
    std::cout << "diff = " << diff << std::endl;
    std::cout << "(diff == float_epsilon) is " << (diff == float_epsilon) << std::endl;
}

template<typename T>
struct name_trait
{
    constexpr static auto name = "undefined name_trait";
};

template<>
struct name_trait<float>
{
    constexpr static auto name = "float";
};

template<>
struct name_trait<double>
{
    constexpr static auto name = "double";
};

template<>
struct name_trait<long double>
{
    constexpr static auto name = "long double";
};

template<typename T>
void inspect_type()
{
    constexpr auto name = name_trait<T>::name;

    std::cout << "std::numeric_limits<" << name << ">::min() = "
        << std::numeric_limits<T>::min() << std::endl;
    std::cout << "std::numeric_limits<" << name << ">::max() = "
        << std::numeric_limits<T>::max() << std::endl;
    std::cout << "std::numeric_limits<" << name << ">::epsilon() = "
        << std::numeric_limits<T>::epsilon() << std::endl;
}

void near_equal_example()
{
    const float d1 = 0.2000001;
    const float d2 = 1 / std::sqrt(5) / std::sqrt(5);
    const float diff = std::abs(d1 - d2);

    std::cout << std::setprecision(20) << "d1 = " << d1
        << "; d2 = " << d2 << std::endl;
    std::cout << "diff = " << diff << std::endl;

    if(d1 == d2)
    {
        std::cout << "d1 == d2\n";
    }
    else
    {
        std::cout << "d1 != d2\n";
    }

    for (int ulp = 0; ulp < 4; ++ulp)
    {
        std::cout << "ulp = " << ulp << ": ";

        if(almost_equal(d1, d2, ulp))
        {
            std::cout << "d1 almost equals d2\n";
        }
        else
        {
            std::cout << "d1 does not almost equal d2\n";
        }
    }
}

int main()
{
    inspect_type<float>();
    inspect_type<double>();
    inspect_type<long double>();

    explore_ulp(0x3f9e0651);
    explore_ulp(0x4ceb79a2);
    explore_ulp(0x7f7fffff);

    near_equal_example();

    return 0;
}
```
