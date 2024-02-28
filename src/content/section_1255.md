# Section 1255

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case ASSIGN_FONT_INT:
    if (chr_code == 0) {
        print_esc("hyphenchar");
    }
    else {
        print_esc("skewchar");
    }
    break;
```
