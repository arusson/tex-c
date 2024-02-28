# Section 1035

If *link(cur_q)* is nonnull when *wrapup* is invoked, *cur_q* points to the list of characters that were consumed while building the ligature character&nbsp;*cur_l*.

A discretionary break is not inserted for an explicit hyphen when we are in restricted horizontal mode.
In particular, this avoids putting discretionary nodes inside of other discretionaries.

```c include/builder.h
// the parameter is either |rt_hit| or |false|
#define pack_lig(X)                                    \
    main_p = new_ligature(main_f, cur_l, link(cur_q)); \
    if (lft_hit) {                                     \
        subtype(main_p) = 2;                           \
        lft_hit = false;                               \
    }                                                  \
    if ((X) && lig_stack == null) {                    \
        incr(subtype(main_p));                         \
        rt_hit = false;                                \
    }                                                  \
    link(cur_q) = main_p;                              \
    tail = main_p;                                     \
    ligature_present = false

#define wrapup(X)                                           \
    do {                                                    \
        if (cur_l < NON_CHAR) {                             \
            if (link(cur_q) > null                          \
                && character(tail) == hyphen_char[main_f])  \
            {                                               \
                ins_disc = true;                            \
            }                                               \
            if (ligature_present) {                         \
                pack_lig((X));                              \
            }                                               \
            if (ins_disc) {                                 \
                ins_disc = false;                           \
                if (mode > 0) {                             \
                    tail_append(new_disc());                \
                }                                           \
            }                                               \
        }                                                   \
    } while (0)
```

```c << Make a ligature node, if |ligature_present|; insert a null discretionary, if appropriate >>=
wrapup(rt_hit);
```
