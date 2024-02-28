# Section 1214

The previous routine does not have to adjust *a* so that *a* **mod** *4 = 0*, since the following routines test for the `\global` prefix as follows.

```c include/builder.h
#define global (a >= 4)
#define define(...)                  \
    do {                             \
        if (global) {                \
            geq_define(__VA_ARGS__); \
        }                            \
        else {                       \
            eq_define(__VA_ARGS__);  \
        }                            \
    } while (0)

#define word_define(...)                  \
    do {                                  \
        if (global) {                     \
            geq_word_define(__VA_ARGS__); \
        }                                 \
        else {                            \
            eq_word_define(__VA_ARGS__);  \
        }                                 \
    } while (0)
```

```c << Adjust for the setting of \globaldefs >>=
if (global_defs != 0) {
    if (global_defs < 0) {
        if (global) {
            a -= 4;
        }
    }
    else if (!global) {
        a += 4;
    }
}
```
