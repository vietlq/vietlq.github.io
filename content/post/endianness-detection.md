+++
draft = false
thumbnail = ""
tags = ["dev", "c++", "tips", "sparc", "x86", "endian"]
categories = []
date = "2018-06-17T08:34:57+01:00"
title = "Endianness Detection the Hard Way"
description = "Learn how to detect Big/Little Endian architectures at run time and compile time, the hard way."
+++

Recently I have had a project that involves serialisation (again!). I have written countless serialisers and deserialisers in 8 years of professional experience. As it goes with binary serialisation, you need to worry about Endianness of your machine because you want your code to be portable across multiple architectures. Text serialisations to JSON or mere CSV exempt you from all that headache, but they are too verbose and slow. In this post I will walk you through tricks to detect Endianness.

## Background

There are two most popular Endian systems: Little Endian and Big Endian. In plain English, Endianness means the convention to represent integral and floating point numbers and where the least significant byte is stored. Little Endian store the lowest byte at lower address space. Big Endian store the lowest byte at higher address space.

There's also PDP Endian that sounds like it was a mistake. Little Endian systems have taken over the world of laptops and PCs with popularity of Intel chips. Macintosh used to have PPC Big Endian chips but that was deprecate in favour for Intel chips that are Little Endian.

Let's look how a 32-bit/4-byte numbers are represented in various Endian systems:

```
int32_t num   = 1;

BIG ENDIAN    => 0x00000001 => {0, 0, 0, 1}
LITTLE ENDIAN => 0x01000000 => {1, 0, 0, 0}
PDP ENDIAN    => 0x00010000 => {0, 1, 0, 0}
```

If you are writing code that need to serialise data over the write and communicate with other computers (IBM AIX, Sun/Oracle Solaris), you will have to worry about portability across Big & Little Endian machines.

Engineers who worked with networked applications in C/C++ probably are acutely aware of the following functions:

```
// https://linux.die.net/man/3/htonl
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```

## Run-time Endianness Detection

Let's start with run-time detection which is nice and easy:

```
bool isBigEndianCast()
{
    const int i = 1;

    return (reinterpret_cast<const char *>(&i)[3] == 1);
}

bool isBigEndianUnion()
{
    union {
        int i;
        char c[4];
    } u;

    u.i = 1;

    return (u.c[3] == 1);
}
```

Those functions work as expected and still backward compatible with C++03. However they are inefficient because you have to call them again and again just to detect Endianness. We need to cache/store their values.

## Compile-time Endianness with a Twist

A C++ developer worth his/her salt can see an optimisation we can perform and force compile-time evaluation by using static const member data:

```
struct EndianUtil
{
    static bool isBigEndianCast()
    {
        const int i = 1;

        return (reinterpret_cast<const char *>(&i)[3] == 1);
    }

    static bool isBigEndianUnion()
    {
        union {
            int i;
            char c[4];
        } u;

        u.i = 1;

        return (u.c[3] == 1);
    }

    static const bool IS_BIG_ENDIAN;
};

const bool EndianUtil::IS_BIG_ENDIAN = EndianUtil::isBigEndianCast();
```

This is again C++03 backward compatible and can be used for AIX & Solaris. The obvious downside is we can't use `EndianUtil::IS_BIG_ENDIAN` for constructing templates because it's evaluated later.

## Compile-time Endianness with C++11 constexpr

Let's go liberal a little bit and jump straight to C++11:

```
class EndianUtil
{
    union temp_union {
        int i;
        char c[4];
    };

    static constexpr temp_union u{1};
    static constexpr int ENDIAN_TEST_NUM = 1;

public:
    // Clang error: constexpr function never produces a constant expression [-Winvalid-constexpr]
    static constexpr bool isBigEndianUnion()
    {
        // Clang error: read of member 'c' of union with active member 'i' is not allowed in a constant expression
        return (u.c[3] == 1);
    }

    // Clang error: constexpr function never produces a constant expression [-Winvalid-constexpr]
    static constexpr bool isLittleEndianUnion()
    {
        // Clang error: read of member 'c' of union with active member 'i' is not allowed in a constant expression
        return (u.c[0] == 1);
    }

    // Clang error: constexpr function never produces a constant expression [-Winvalid-constexpr]
    static constexpr bool isBigEndianCast()
    {
        // Clang error: reinterpret_cast is not allowed in a constant expression
        return (reinterpret_cast<const char *>(&ENDIAN_TEST_NUM)[3] == 1);
    }

    // Clang error: constexpr function never produces a constant expression [-Winvalid-constexpr]
    static constexpr bool isLittleEndianCast()
    {
        // Clang error: reinterpret_cast is not allowed in a constant expression
        return (reinterpret_cast<const char *>(&ENDIAN_TEST_NUM)[0] == 1);
    }
};
```

This code works perfectly with GCC 4.7.4 but fails miserably for Clang. The reason for regression is: Clang is much more strict about `constexpr` and GCC has relaxed condition for `constexpr`. Both C++11 and C++14 support in Clang rejects such flexible usage of `constexpr`. Since we are looking for a portable Endianness detection, let's not rest on our laurels and make an extra leap.

## Compile-time Endianness with Macros

The perfect solution should satisfy two criteria:

* Be C++03 compatible because AIX and Solaris are not going to add C++11 support any time soon (probably never)
* Can be used for template construction (in-case we want `std::enable_if` and friends)

We can only achieve that with C/C++ pre-processors and macros. I found some useful links for constructing our solution:

* https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
* https://sourceforge.net/p/predef/wiki/Endianness/
* http://esr.ibiblio.org/?p=5095

The following code was adapted from http://esr.ibiblio.org/?p=5095 :

```
enum endian_t {
    OS_LITTLE_ENDIAN   = 0x00000001,
    OS_BIG_ENDIAN      = 0x01000000,
    OS_PDP_ENDIAN      = 0x00010000,
    OS_UNKNOWN_ENDIAN  = 0xFFFFFFFF
};

#ifdef __BIG_ENDIAN__
enum { OS_BYTE_ORDER = OS_BIG_ENDIAN };
#else /* NO __BIG_ENDIAN__ */
#ifdef __LITTLE_ENDIAN__
enum { OS_BYTE_ORDER = OS_LITTLE_ENDIAN };
#else /* NO __LITTLE_ENDIAN__ */
#ifdef BSD
#include <sys/endian.h>
#else // BSD
#include <endian.h>
#endif // BSD
#if __BYTE_ORDER == __BIG_ENDIAN
enum { OS_BYTE_ORDER = OS_BIG_ENDIAN };
#elif __BYTE_ORDER == __LITTLE_ENDIAN
enum { OS_BYTE_ORDER = OS_LITTLE_ENDIAN };
#else
#error "Unsupported Endianness!"
#endif /* __BYTE_ORDER */
#endif /* __LITTLE_ENDIAN__ */
#endif /* __BIG_ENDIAN__ */
```

Now you can happily use the work above for templates:

```
#include <iostream>
#include <string>

template<int V = OS_BYTE_ORDER>
struct Endianness
{
    const static std::string endianness()
    {
        return "OS_BYTE_ORDER";
    }
};

template<>
struct Endianness<OS_LITTLE_ENDIAN>
{
    const static std::string endianness()
    {
        return "OS_LITTLE_ENDIAN";
    }
};

template<>
struct Endianness<OS_BIG_ENDIAN>
{
    const static std::string endianness()
    {
        return "OS_BIG_ENDIAN";
    }
};

typedef Endianness<> EndianUtil;

int main()
{
    std::cout << EndianUtil::endianness() << std::endl;

    return 0;
}
```

## Closing & Next Post

From the start to the end we didn't discuss how can we test on Big Endian systems. Who said testing was easy, especially when you don't run AIX or Solaris at home? So now code can be only tested on Intel chips. I will detail the steps to test on Big Endian systems (for FREE!) in the next post. Stay tuned!
