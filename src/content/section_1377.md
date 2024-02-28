# Section 1377

```c << Implement \setlanguage >>=
if (abs(mode) != HMODE) {
    report_illegal_case();
}
else {
    new_whatsit(LANGUAGE_NODE, SMALL_NODE_SIZE);
    scan_int();
    if (cur_val <= 0) {
        clang = 0;
    }
    else if (cur_val > 255) {
        clang = 0;
    }
    else {
        clang = cur_val;
    }
    what_lang(tail) = clang;
    what_lhm(tail) = norm_min(left_hyphen_min);
    what_rhm(tail) = norm_min(right_hyphen_min);
}
```
