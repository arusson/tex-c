# Section 351

```c << Finish line, emit a \par >>=
loc = limit + 1;
cur_cs = par_loc;
cur_cmd = eq_type(cur_cs);
cur_chr = equiv(cur_cs);
if (cur_cmd >= OUTER_CALL) {
    check_outer_validity();
}
```
