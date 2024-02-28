# Section 1306

The inverse macros are slightly more complicated, since we need to check the range of the values we are reading in.
We say *'undump(a, b, x)'* to read an integer value *x* that is supposed to be in the range *a* $\leq$ *x* $\leq$ *b*.
System error messages should be suppressed when undumping.

```c include/io.h
#define undump_wd(X)  fread(&X, 8, 1, fmt_file)
#define undump_int(X) fread(&X, 4, 1, fmt_file)
#define undump_hh     undump_wd
#define undump_qqqq   undump_wd

#define undump(A, B, X)       \
    undump_int(x);            \
    if (x < (A) || x > (B)) { \
        goto bad_fmt;         \
    }                         \
    (X) = x

#define undump_size(A, B, S, X) \
    undump_int(x);              \
    if (x < (A)) {              \
        goto bad_fmt;           \
    }                           \
    if (x > (B)) {              \
        too_small(S);           \
    }                           \
    (X) = x
```
