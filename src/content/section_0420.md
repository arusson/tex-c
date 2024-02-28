# Section 420

```c << Fetch a box dimension >>=
scan_eight_bit_int();
if (box(cur_val) == null) {
    cur_val = 0;
}
else {
    cur_val = mem[box(cur_val) + m].sc;
}
cur_val_level = DIMEN_VAL;
```
