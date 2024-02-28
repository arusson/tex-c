# Section 832

The following code uses the fact that *type(LAST_ACTIVE)* $\ne$ *DELTA_NODE*.

```c include/breaker.h
#define update_width(X) cur_active_width[(X)] += mem[r + (X)].sc
```

```c << If node |r| is of type |DELTA_NODE|, update |cur_active_width|, set |prev_r| and |prev_prev_r|, then |goto continue| >>=
if (type(r) == DELTA_NODE) {
    do_all_six(update_width);
    prev_prev_r = prev_r;
    prev_r = r;
    goto continue_lbl;
}
```
