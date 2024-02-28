# Section 1220

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case LET:
    if (chr_code != NORMAL) {
        print_esc("futurelet");
    }
    else {
        print_esc("let");
    }
    break;
```
