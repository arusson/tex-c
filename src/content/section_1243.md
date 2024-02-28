# Section 1243

```c << Declare subprocedures for |prefixed_command| >>+=
void alter_aux() {
    halfword c; // |HMODE| or |VMODE|
    if (cur_chr != abs(mode)) {
        report_illegal_case();
    }
    else {
        c = cur_chr;
        scan_optional_equals();
        if (c == VMODE) {
            scan_normal_dimen;
            prev_depth = cur_val;
        }
        else {
            scan_int();
            if (cur_val <= 0 || cur_val > 32767) {
                print_err("Bad space factor");
                help1("I allow only values in the range 1..32767 here.");
                int_error(cur_val);
            }
            else {
                space_factor = cur_val;
            }
        }
    }
}
```
