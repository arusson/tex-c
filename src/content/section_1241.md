# Section 1241

The processing of boxes is somewhat different, because we may need to scan and create an entire box before we actually change the value of the old one.

```c << Assignments >>+=
case SET_BOX:
    scan_eight_bit_int();
    if (global) {
        n = 256 + cur_val;
    }
    else {
        n = cur_val;
    }
    scan_optional_equals();
    if (set_box_allowed) {
        scan_box(BOX_FLAG + n);
    }
    else {
        print_err("Improper ");
        print_esc("setbox");
        help2("Sorry, \\setbox is not allowed after \\halign in a display,")
            ("or between \\accent and an accented character.");
        error();
    }
    break;
```
