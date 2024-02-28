# Section 1234

```c << Assignments >>+=
case DEF_FAMILY:
    p = cur_chr;
    scan_four_bit_int();
    p += cur_val;
    scan_optional_equals();
    scan_font_ident();
    define(p, DATA, cur_val);
    break;
```
