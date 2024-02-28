# Section 112

The operation of adding or subtracting *MIN_QUARTERWORD* occurs quite frequently in $\TeX$, so it is convenient to abbreviate this operation by using the macros *qi* and *qo* for input and output to and from quarterword format.

The inner loop of $\TeX$ will run faster with respect to compilers that don't optimize expressions like *'x + 0'* and *'x − 0'*, if these macros are simplified in the obvious way when *MIN_QUARTERWORD = 0*.

> ![NOTE]
> No *qi* and *qo*, since *MIN_QUARTERWORD* is 0.

```c include/tex.h
#define hi(X) ((X) + MIN_HALFWORD) // to put a sixteen-bit item into a halfword
#define ho(X) ((X) - MIN_HALFWORD) // to take a sixteen-bit item from a halfword
```
