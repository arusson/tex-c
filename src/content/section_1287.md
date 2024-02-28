# Section 1287

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case CASE_SHIFT:
    if (chr_code == LC_CODE_BASE) {
        print_esc("lowercase");
    }
    else {
        print_esc("uppercase");
    }
    break;
```
