# Section 371

The *expand* procedure and some other routines that construct token lists find it convenient to use the following macros, which are valid only if the variables *p* and *q* are reserved for token-list building.

```c include/parser.h
#define store_new_token(X) \
    q = get_avail();       \
    link(p) = q;           \
    info(q) = (X);         \
    p = q // |link(p)| is |null|

#define fast_store_new_token(X) \
    fast_get_avail(q);          \
    link(p) = q;                \
    info(q) = (X);              \
    p = q // |link(p)| is |null|
```
