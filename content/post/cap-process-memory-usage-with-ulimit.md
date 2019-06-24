+++
draft = false
tags = []
categories = []
date = "2019-06-24T20:02:35+01:00"
title = "Cap Process Memory Usage With ulimit"
highlight = true
description = "How to set hard limit on memory usage of child process with ulimit"
thumbnail = ""
+++

Let's say your process has unpredictable memory usage with many spikes, or even worse, a long-running process with memory leaks. The third use case is when you recompile your application from 32-bit to 64-bit and instead of hard limit of 4GB imposed by the OS, your process now can consume up to 16 exabytes. Realistically your server can have a few hundred GB, means a misbehaving and RAM hungry process can blow up and bring down a whole server.

What you want to do in those cases is to limit RAM usage in those cases and make sure the process is prevented from acquiring memory when it has consumed above certain threshold.