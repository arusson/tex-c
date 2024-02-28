# Section 455

```c << Scan for units that are internal dimensions; |goto attach_sign| with |cur_val| set if found >>=
save_cur_val = cur_val;
// << Get the next non-blank non-call token >>
if (cur_cmd < MIN_INTERNAL || cur_cmd > MAX_INTERNAL) {
    back_input();
}
else {
    if (mu) {
        scan_something_internal(MU_VAL, false);
        // << Coerce glue to a dimension >>
        if (cur_val_level != MU_VAL) {
            mu_error();
        }
    }
    else {
        scan_something_internal(DIMEN_VAL, false);
    }
    v = cur_val;
    goto found;
}
if (mu) {
    goto not_found;
}
if (scan_keyword("em")) {
    // << The em width for |cur_font| >>
}
else if (scan_keyword("ex")) {
    // << The x-height for |cur_font| >>
}
else {
    goto not_found;
}
// << Scan an optional space >>

found:
cur_val = nx_plus_y(save_cur_val, v, xn_over_d(v, f, 0x10000));
goto attach_sign;
not_found:
```
