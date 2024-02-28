# Section 449

```c << Fetch an internal dimension and |goto attach_sign|, or fetch an internal integer >>=
if (mu) {
    scan_something_internal(MU_VAL, false);
    // << Coerce glue to a dimension >>
    if (cur_val_level == MU_VAL) {
        goto attach_sign;
    }
    if (cur_val_level != INT_VAL) {
        mu_error();
    }
}
else {
    scan_something_internal(DIMEN_VAL, false);
    if (cur_val_level == DIMEN_VAL) {
        goto attach_sign;
    }
}
```
