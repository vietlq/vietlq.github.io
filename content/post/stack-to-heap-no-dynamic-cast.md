+++
categories = []
date = "2017-05-02T21:49:55+01:00"
draft = true
tags = ["c++", "heap", "inheritance"]
thumbnail = ""
title = "Stack to Heap no Dynamic Cast"
description = "Noob Interview Question: Stack to Heap no Dynamic Cast"
+++

http://stackoverflow.com/questions/43746761/not-using-dynamic-cast

```
There is an abstract class BasePet and some child classes. I want to make a function

BasePet* foo(BasePet*);
which will make copies of objects from static memory to heap. Is there any way except using dynamic_cast? (For example, if there may be another child classes which are unknown for me and I want foo() to be usable for them all).
```

```
You can create a clone and override it for each class.
```
