# Section 1253

All of $\TeX$'s parameters are kept in *eqtb* except the font information, the interaction mode, and the hyphenation tables; these are strictly global.

```c << Assignments >>+=
case ASSIGN_FONT_DIMEN:
    find_font_dimen(true);
    k = cur_val;
    scan_optional_equals();
    scan_normal_dimen;
    font_info[k].sc = cur_val;
    break;

case ASSIGN_FONT_INT:
    n = cur_chr;
    scan_font_ident();
    f = cur_val;
    scan_optional_equals();
    scan_int();
    if (n == 0) {
        hyphen_char[f] = cur_val;
    }
    else {
        skew_char[f] = cur_val;
    }
    break;
```
