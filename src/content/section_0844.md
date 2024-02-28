# Section 844

When the following code is performed, we will have just inserted at least one active node before *r*, so *type(prev_r)* $\ne$ *DELTA_NODE*.

```c include/breaker.h
#define new_delta_from_break_width(X) mem[q + (X)].sc = cur_active_width[(X)] - break_width[(X)]
```

```c << Insert a delta node to prepare for the next active node >>=
if (r != LAST_ACTIVE) {
    q = get_node(DELTA_NODE_SIZE);
    link(q) = r;
    type(q) = DELTA_NODE;
    subtype(q) = 0; // the |subtype| is not used
    do_all_six(new_delta_from_break_width);
    link(prev_r) = q;
    prev_prev_r = prev_r;
    prev_r = q;
}
```
