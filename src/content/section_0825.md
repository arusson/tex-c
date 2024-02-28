# Section 825

Glue nodes in a horizontal list that is being paragraphed are not supposed to include "infinite" shrinkability; that is why the algorithm maintains four registers for stretching but only one for shrinking.
If the user tries to introduce infinite shrinkability, the shrinkability will be reset to finite and an error message will be issued.
A boolean variable *no_shrink_error_yet* prevents this error message from appearing more than once per paragraph.

```c include/breaker.h
#define check_shrinkage(X)                                     \
    do {                                                       \
        if (shrink_order((X)) != NORMAL && shrink((X)) != 0) { \
            (X) = finite_shrink((X));                          \
        }                                                      \
    } while (0)
```

```c << Global variables >>+=
bool no_shrink_error_yet; // have we complained about infinite shrinkage?
```
