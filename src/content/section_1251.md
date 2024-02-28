# Section 1251

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case HYPH_DATA:
    if (chr_code == 1) {
        print_esc("patterns");
    }
    else {
        print_esc("hyphenation");
    }
    break;
```
