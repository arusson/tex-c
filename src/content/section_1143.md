# Section 1143

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case EQ_NO:
    if (chr_code == 1) {
        print_esc("leqno");
    }
    else {
        print_esc("eqno");
    }
    break;
```
