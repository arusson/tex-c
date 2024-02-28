# Section 1231

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case DEF_CODE:
    if (chr_code == CAT_CODE_BASE) {
        print_esc("catcode");
    }
    else if (chr_code == MATH_CODE_BASE) {
        print_esc("mathcode");
    }
    else if (chr_code == LC_CODE_BASE) {
        print_esc("lccode");
    }
    else if (chr_code == UC_CODE_BASE) {
        print_esc("uccode");
    }
    else if (chr_code == SF_CODE_BASE) {
        print_esc("sfcode");
    }
    else {
        print_esc("delcode");
    }
    break;

case DEF_FAMILY:
    print_size(chr_code - MATH_FONT_BASE);
    break;
```
