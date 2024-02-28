# Section 577

Before we forget about the format of these tables, let's deal with two of $\TeX$'s basic scanning routines related to font information.

```c << Declare procedures that scan font-related stuff >>=
void scan_font_ident() {
    internal_font_number f;
    halfword m;
    // << Get the next non-blank non-call token >>
    if (cur_cmd == DEF_FONT) {
        f = cur_font;
    }
    else if (cur_cmd == SET_FONT) {
        f = cur_chr;
    }
    else if (cur_cmd == DEF_FAMILY) {
        m = cur_chr;
        scan_four_bit_int();
        f = equiv(m + cur_val);
    }
    else {
        print_err("Missing font identifier");
        help2("I was looking for a control sequence whose")
            ("current meaning has been defined by \\font.");
        back_error();
        f = NULL_FONT;
    }
    cur_val = f;
}
```
