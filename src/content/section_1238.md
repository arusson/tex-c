# Section 1238

```c << Compute result of |REGISTER| or |ADVANCE|, put it in |cur_val| >>=
if (p < GLUE_VAL) {
    if (p == INT_VAL) {
        scan_int();
    }
    else {
        scan_normal_dimen;
    }
    if (q == ADVANCE) {
        cur_val += eqtb[l].integer;
    }
}
else {
    scan_glue(p);
    if (q == ADVANCE) {
        // << Compute the sum of two glue specs >>
    }
}
```
