# Section 1246

```c << Declare subprocedures for |prefixed_command| >>+=
void alter_integer() {
    int c; // 0 for \deadcycles, 1 for \insertpenalties
    c = cur_chr;
    scan_optional_equals();
    scan_int();
    if (c == 0) {
        dead_cycles = cur_val;
    }
    else {
        insert_penalties = cur_val;
    }
}
```
