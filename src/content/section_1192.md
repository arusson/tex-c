# Section 1192

```c << Try to recover from mismatched \right >>=
if (cur_group == MATH_SHIFT_GROUP) {
    scan_delimiter(GARBAGE, false);
    print_err("Extra ");
    print_esc("right");
    help1("I'm ignoring a \\right that had no matching \\left.");
    error();
}
else {
    off_save();
}
```
