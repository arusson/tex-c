# Section 910

```c include/breaker.h
#define wrap_lig(X)                                   \
    do {                                              \
        if (ligature_present) {                       \
            p = new_ligature(hf, cur_l, link(cur_q)); \
            if (lft_hit) {                            \
                subtype(p) = 2;                       \
                lft_hit = false;                      \
            }                                         \
            if ((X) && lig_stack == null) {           \
                incr(subtype(p));                     \
                rt_hit = false;                       \
            }                                         \
            link(cur_q) = p;                          \
            t = p;                                    \
            ligature_present = false;                 \
        }                                             \
    } while (0)

#define pop_lig_stack                                \
    do {                                             \
        if (lig_ptr(lig_stack) > null) {             \
            /* this is a charnode for |hu[j + 1]| */ \
            link(t) = lig_ptr(lig_stack);            \
            t = link(t);                             \
            incr(j);                                 \
        }                                            \
        p = lig_stack;                               \
        lig_stack = link(p);                         \
        free_node(p, SMALL_NODE_SIZE);               \
        if (lig_stack == null) {                     \
            set_cur_r;                               \
        }                                            \
        else {                                       \
            cur_r = character(lig_stack);            \
        }                                            \
    } while (0)
// if |lig_stack| isn't |null| we have |cur_rh = NON_CHAR|
```

```c << Append a ligature and/or kern to the translation; |goto continue| if the stack of inserted ligatures is nonempty >>=
wrap_lig(rt_hit);
if (w != 0) {
    link(t) = new_kern(w);
    t = link(t);
    w = 0;
}
if (lig_stack > null) {
    cur_q = t;
    cur_l = character(lig_stack);
    ligature_present = true;
    pop_lig_stack;
    goto continue_lbl;
}
```
