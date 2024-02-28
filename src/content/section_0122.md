# Section 122

There's also a *fast_get_avail* routine, which saves the procedure-call overhead at the expense of extra programming.
This routine is used in the places that would otherwise account for the most calls of *get_avail*.

```c include/datastructures.h
#define fast_get_avail(X)                                 \
    do {                                                  \
        /* avoid |get avail| if possible, to save time */ \
        (X) = avail;                                      \
        if ((X) == null) {                                \
            (X) = get_avail();                            \
        }                                                 \
        else {                                            \
            avail = link((X));                            \
            link((X)) = null;                             \
            incr_dyn_used;                                \
        }                                                 \
    } while(0)
```
