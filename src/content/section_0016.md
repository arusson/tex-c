# Section 16

Here are some macros for common programming idioms.

> ![NOTE]
> *odd* and *abs* definitions are added here.

```c include/constants.h
#define EMPTY 0 // symbolic name for a null constant
```

```c include/tex.h
#define incr(X)    (X) += 1   // increase a variable by unity
#define decr(X)    (X) -= 1   // decrease a variable by unity
#define negate(X)  (X) = -(X) // change the sign of a variable
#define do_nothing
#define odd(X)     ((X) & 1)
#define abs(X)     (((X) >= 0) ? (X) : -(X))
```
