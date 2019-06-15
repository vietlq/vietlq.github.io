+++
css = []
date = "2017-06-03T18:04:22+01:00"
description = "Listing all header files your cpp depends on"
scripts = []
draft = false
highlight = true
tags = ["c++", "dev", "tips", "tools", "tutorial"]
categories = []
title = "Listing all header files your cpp depends on"
thumbnail = "pimages/00044-official-cpp-logo.png"
+++

I needed to extract certain Boost headers from its huge code base for memory mapped file & shared memory containers. The first idea came to my mind was a simple grep command for `#include` statements and then parse the paths. This is simple but not so useful for the cases when headers are conditionally included. For example:

```c++
#ifndef NO_STL
#include "my_class_no_stl.h"
#else
#include "my_class_stl.h"
#endif
```

To be honest, grep won’t be able to handle it. We need a full fledged C++ pre-processor to correctly include headers and pass necessary values/definitions (it’s done with -D for g++). I was struggling a bit and got a tip from Ralph. It turned out to be very simple:

```bash
g++ -D NO_STL -I A_PATH -M source.cpp # to get all headers, including system headers
g++ -D NO_STL -I A_PATH -MM source.cpp # to get all headers, except system headers
g++ -D NO_STL -I A_PATH -H source.cpp # to print all headers nested in as a tree
```

Source: http://stackoverflow.com/questions/5834778/g-how-to-tell-where-a-header-file-is-included-from
