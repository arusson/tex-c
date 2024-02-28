# Section 353

```c << Process an active-character control sequence and set |state = MID_LINE| >>=
cur_cs = cur_chr + ACTIVE_BASE;
cur_cmd = eq_type(cur_cs);
cur_chr = equiv(cur_cs);
state = MID_LINE;
if (cur_cmd >= OUTER_CALL) {
    check_outer_validity();
}
```
