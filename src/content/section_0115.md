# Section 115: Dynamic memory allocation

The $\TeX$ system does nearly all of its own memory allocation, so that it can readily be transported into environments that do not have automatic facilities for strings, garbage collection, etc., and so that it can be in control of what error messages the user receives.
The dynamic storage requirements of $\TeX$ are handled by providing a large array *mem* in which consecutive blocks of words are used as nodes by the $\TeX$ routines.

Pointer variables are indices into this array, or into another array called *eqtb* that will be explained later.
A pointer variable might also be a special flag that lies outside the bounds of *mem*, so we
allow pointers to assume any *halfword* value.
The minimum halfword value represents a null pointer. $\TeX$ does not assume that *mem[null]* exists.

> ![NOTE]
> All constants are written in uppercase in this implementation, however, the `NULL` keyword is a reserved word in C, so an exception is made for the $\TeX$ null pointer.

```c include/constants.h
#define null MIN_HALFWORD // the null pointer
```

```c << Types in the outer block >>+=
typedef halfword pointer; // a flag or a location in |mem| or |eqtb|
```

```c << Global variables >>+=
pointer temp_ptr; // a pointer variable for occasional emergency use
```
