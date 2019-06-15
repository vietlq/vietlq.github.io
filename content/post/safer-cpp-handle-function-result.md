+++
draft = false
tags = ["tips", "c++", "dev", "cpp", "compiler", "safety", "security"]
categories = []
date = "2018-05-12T18:15:05+01:00"
title = "Safer C++ By Handling Function Result"
description = "Learn how to force C++ developers to handle function result for safety using function attributes and compiler flags"
thumbnail = "pimages/00042-cpp-fruity.png"
+++

Despite best efforts to train, educate, warn developers to always capture and handle function results, one still can manage to forget and get burned in the process. Let's say you have this piece of code that deals with critical process:

```
int critical_func()
{
    return 1234;
}
```

It's far too common for folks to use `critical_func()` in this manner:

```
int use_critical_func()
{
    critical_func();

    return 0;
}
```

The values returned from `critical_func()` could mean anything: Cannot connect to a service, balance is empty, rocket is faulty, ... Failure to capture and act based on those return values could result in any undefined/undesired behaviour: Memory leak, crash, silent failures, ...

Unfortunately most C/C++ compilers have no way to detect the issue. Not all is lost. I have some good news! People who use GCC/Clang are blessed because they have access to function flag `__attribute__((warn_unused_result))` and compiler flag `-Wunused-result`. When combined together, these 2 flags will detect the cases when the annotated function has its result discarded:

```
// https://gcc.gnu.org/onlinedocs/gcc-4.7.2/gcc/Function-Attributes.html
// https://infektor.net/posts/2017-01-19-using-cpp17-attributes-today.html
// Compiler flags: -Wall -Werror -Wextra -pedantic -Wunused-result -std=c++11
// Suggested macro names: HANDLE_OUTPUT / NODISCARD / MUST_HANDLE

#define HANDLE_OUTPUT __attribute__((warn_unused_result))

HANDLE_OUTPUT int critical_func()
{
    return 1234;
}

template<typename ... Args>
void ignore(Args && ...)
{
}

int use_critical_func()
{
    // This will cause the warning: [x86-64 gcc 7.2 #1] error: ignoring return value of 'int critical_func()',
    // declared with attribute warn_unused_result [-Werror=unused-result]
    //critical_func();

    // This will pass
    ignore(critical_func());

    return 0;
}
```

Unlike OCaml where you have to explicitly ignore function result, by default C/C++ just ignore function results, opening a can of worms. You will have to make conscious effort to detect the cases like above. However, if you work in financial industry where every single line of code carries weight and affects clients' PnL, you will thank me and keep using this feature from now on.

Image source: https://www.pngfly.com/png-s148bc/
