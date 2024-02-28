# Section 101

Fixed-point arithmetic is done on *scaled integers* that are multiples of $2^{-16}$.
In other words, a binary point is assumed to be sixteen bit positions from the right end of a binary computer word.

```c include/constants.h
#define UNITY 65536  // 2^{16}, represents 1.00000
#define TWO   131072 // 2^{17}, represents 2.00000
```

```c << Types in the outer block >>+=
typedef int scaled; // this is used for scaled integer
typedef unsigned char small_number; // this type is self-explanatory
```
