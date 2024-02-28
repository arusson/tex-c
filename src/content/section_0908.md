# Section 908

```c include/breaker.h
#define append_charnode_to_t(X) \
    link(t) = get_avail();      \
    t = link(t);                \
    font(t) = hf;               \
    character(t) = (X)

#define set_cur_r              \
    do {                       \
        if (j < n) {           \
            cur_r = hu[j + 1]; \
        }                      \
        else {                 \
            cur_r = bchar;     \
        }                      \
        if (odd(hyf[j])) {     \
            cur_rh = hchar;    \
        }                      \
        else {                 \
            cur_rh = NON_CHAR; \
        }                      \
    } while (0)
```

```c << Set up data structures with the cursor following position |j| >>=
cur_l = hu[j];
cur_q = t;
if (j == 0) {
    ligature_present = init_lig;
    p = init_list;
    if (ligature_present) {
        lft_hit = init_lft;
    }
    while (p > null) {
        append_charnode_to_t(character(p));
        p = link(p);
    }
}
else if (cur_l < NON_CHAR) {
    append_charnode_to_t(cur_l);
}
lig_stack = null;
set_cur_r;
```
