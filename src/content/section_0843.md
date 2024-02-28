# Section 843

We use the fact that *type(ACTIVE)* $\ne$ *DELTA_NODE*.

```c include/breaker.h
#define convert_to_break_width(X)   mem[prev_r + (X)].sc += (-cur_active_width[(X)] + break_width[(X)])
#define store_break_width(X)        active_width[(X)] = break_width[(X)]
#define new_delta_to_break_width(X) mem[q + (X)].sc = break_width[(X)] - cur_active_width[(X)]
```

```c << Insert a delta node to prepare for breaks at |cur_p| >>=
if (type(prev_r) == DELTA_NODE) {
    // modify an existing delta node
    do_all_six(convert_to_break_width);
}
else if (prev_r == ACTIVE) {
    // no delta node needed at the beginning
    do_all_six(store_break_width);
}
else {
    q = get_node(DELTA_NODE_SIZE);
    link(q) = r;
    type(q) = DELTA_NODE;
    subtype(q) = 0; // the |subtype| is not used
    do_all_six(new_delta_to_break_width);
    link(prev_r) = q;
    prev_prev_r = prev_r;
    prev_r = q;
}
```
