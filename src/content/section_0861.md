# Section 861

The following code uses the fact that *type(LAST_ACTIVE)* $\ne$ *DELTA_NODE*.
If the active list has just become empty, we do not need to update the *active_width* array, since it will be initialized when an active node is next inserted.

```c include/breaker.h
#define update_active(X) active_width[(X)] += mem[r + (X)].sc
```

```c << Update the active widths, since the first active node has been deleted >>=
r = link(ACTIVE);
if (type(r) == DELTA_NODE) {
    do_all_six(update_active);
    do_all_six(copy_to_cur_active);
    link(ACTIVE) = link(r);
    free_node(r, DELTA_NODE_SIZE);
}
```
