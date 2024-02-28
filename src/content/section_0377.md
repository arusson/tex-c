# Section 377

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case INPUT:
    if (chr_code == 0) {
        print_esc("input");
    }
    else {
        print_esc("endinput");
    }
    break;
```
