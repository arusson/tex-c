# Section 1362

```c include/extensions.h
#define adv_past(X)                          \
    do {                                     \
        if (subtype((X)) == LANGUAGE_NODE) { \
            cur_lang = what_lang((X));       \
            l_hyf = what_lhm((X));           \
            r_hyf = what_rhm((X));           \
        }                                    \
    } while(0)
```

```c << Advance past a whatsit node in the |line_break| loop >>=
adv_past(cur_p);
```
