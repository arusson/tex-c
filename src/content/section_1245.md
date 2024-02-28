# Section 1245

```c << Declare subprocedures for |prefixed_command| >>+=
void alter_page_so_far() {
    int c; // index into |page_so_far|
    c = cur_chr;
    scan_optional_equals();
    scan_normal_dimen;
    page_so_far[c] = cur_val;
}
```
