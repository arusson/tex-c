# Section 422

```c << Fetch the |prev_graf| >>=
if (mode == 0) {
    scanned_result(0, INT_VAL); // |prev_graf == 0| within \write
}
else {
    nest[nest_ptr] = cur_list;
    p = nest_ptr;
    while (abs(nest[p].mode_field) != VMODE) {
        decr(p);
    }
    scanned_result(nest[p].pg_field, INT_VAL);
}
```
