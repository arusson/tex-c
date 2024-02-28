# Section 316

The following code sets up the print routines so that they will gather the desired information.

```c include/io.h
#define begin_pseudoprint  \
    l = tally;             \
    tally = 0;             \
    selector = PSEUDO;     \
    trick_count = 1000000

#define set_trick_count                                         \
    do {                                                        \
        first_count = tally;                                    \
        trick_count = tally + 1 + ERROR_LINE - HALF_ERROR_LINE; \
        if (trick_count < ERROR_LINE) {                         \
            trick_count = ERROR_LINE;                           \
        }                                                       \
    } while (0)
```
