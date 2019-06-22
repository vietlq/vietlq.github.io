+++
draft = false
tags = ["dev", "c++", "tips", "sparc", "x86", "endian"]
categories = []
date = "2019-06-22T14:59:34+01:00"
title = "Endianness Agnostic ntoh"
highlight = true
description = "Writing Endianness agnostic ntoh/hton functions"
thumbnail = ""
+++

From the [Endianness detection blog entry]({{< relref "endianness-detection.md" >}}), we have learned how to do that using predefined macros across different architectures. Our next task is to write `ntoh` (network to host) and `hton` (host to network) functions to convert integers and floating point values between network and host formats. Here's a catch: Do not use conditionals - basically, do not use any of the keywords `if/else/for/while`. Let's start with `int ntoh(int)`. We know that Big Endian and Little Endian machines have different memory layout for the same integer and floating point values. Let's say our integer of value `0x12345678` is allocated at the address `0xaabbcc00`. Now we have 2 different memory layouts:

```
Big Endian layout (the least signinificant bytes at has the highest address):
0xaabbcc00 0x12
0xaabbcc01 0x34
0xaabbcc02 0x56
0xaabbcc03 0x78

Little Endian layout (the most signinificant bytes at has the highest address):
0xaabbcc00 0x78
0xaabbcc01 0x56
0xaabbcc02 0x34
0xaabbcc03 0x12
```

Based on this, we can deduce a trick to force conversion the address of an integer to `const char *` and treat the 4 consecutive bytes as 4 separate 8-bit integers. It's known that the network byte order is Big Endian, so the first byte is the most significant byte as well, and we shift it left by 24 bits. The second byte is shifted 16 bits and the third byte is shifted 8 bits to the left. The least significant byte is the fourth byte, it requires no shifting:

```c
// C code
int ntoh(int n) {
    const char * temp = (const char *)&n;
    return (temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | temp[3];
}
```

```cpp
// C++ code
int ntoh(int n) {
    const char * temp = reinterpret_cast<const char *>(&n);
    return (temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | temp[3];
}
```

So we know that this works on Big Endian machines. But will it work on Little Endian machines? The input number has different layout compared to Little Endian host order. However, when we perform the casting to `const char *` on Little Endian machines, we essentially force byte swap operation. Therefore, the reconstruction will work as expected too.

To see how efficient is the code, I decided to look at the [compiler explorer website](https://godbolt.org). The code generated for x86-64 using Clang 5.0 from https://godbolt.org is quite short:

```asm
ntoh(int): # @ntoh(int)
  push rbp
  mov rbp, rsp
  lea rax, [rbp - 4]
  mov dword ptr [rbp - 4], edi
  mov qword ptr [rbp - 16], rax
  mov rax, qword ptr [rbp - 16]
  movsx edi, byte ptr [rax]
  shl edi, 24
  mov rax, qword ptr [rbp - 16]
  movsx ecx, byte ptr [rax + 1]
  shl ecx, 16
  or edi, ecx
  mov rax, qword ptr [rbp - 16]
  movsx ecx, byte ptr [rax + 2]
  shl ecx, 8
  or edi, ecx
  mov rax, qword ptr [rbp - 16]
  movsx ecx, byte ptr [rax + 3]
  or edi, ecx
  mov eax, edi
  pop rbp
  ret
```

Look, there are no conditionals (and hence, no loops)! You can repeat the same process for other integral and floating point types without using loops. I hope you don't mind some typing!

We could push a little more and write a byte-swapping function `int byteswap(int)` to swap Endianness of a number. The code is just short and requires no casting and no conditionals:

```c
int byteswap(int n) {
    return ((n & 0xff) << 24) | ((n & 0xff00) << 8) | ((n & 0xff0000) >> 8) | (n >> 24);
}
```

The assembly code for x86-64 using Clang 5.0 generated is also succint:

```
byteswap(int): # @byteswap(int)
  push rbp
  mov rbp, rsp
  mov dword ptr [rbp - 4], edi
  mov edi, dword ptr [rbp - 4]
  and edi, 255
  shl edi, 24
  mov eax, dword ptr [rbp - 4]
  and eax, 65280
  shl eax, 8
  or edi, eax
  mov eax, dword ptr [rbp - 4]
  and eax, 16711680
  sar eax, 8
  or edi, eax
  mov eax, dword ptr [rbp - 4]
  sar eax, 24
  or edi, eax
  mov eax, edi
  pop rbp
  ret
```

I'll leave to the readers to write template-tised version of the above functions for the remaining integral and floating point types.