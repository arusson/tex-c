# Section 860

When an active node disappears, we must delete an adjacent delta node if the active node was at the beginning or the end of the active list, or if it was surrounded by delta nodes.
We also must preserve the property that *cur_active_width* represents the length of material from *link(prev_r)* to&nbsp;*cur_p*.

```c include/breaker.h
#define combine_two_deltas(X) mem[prev_r + (X)].sc += mem[r + (X)].sc
#define downdate_width(X)     cur_active_width[(X)] -= mem[prev_r + (X)].sc
```

```c << Deactivate node |r| >>=
link(prev_r) = link(r);
free_node(r, ACTIVE_NODE_SIZE);
if (prev_r == ACTIVE) {
    // << Update the active widths, since the first active node has been deleted >>
}
else if (type(prev_r) == DELTA_NODE) {
    r = link(prev_r);
    if (r == LAST_ACTIVE) {
        do_all_six(downdate_width);
        link(prev_prev_r) = LAST_ACTIVE;
        free_node(prev_r, DELTA_NODE_SIZE);
        prev_r = prev_prev_r;
    }
    else if (type(r) == DELTA_NODE) {
        do_all_six(update_width);
        do_all_six(combine_two_deltas);
        link(prev_r) = link(r);
        free_node(r, DELTA_NODE_SIZE);
    }
}
```
