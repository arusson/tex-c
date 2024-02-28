# Section 1115

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case DISCRETIONARY:
    if (chr_code == 1) {
        print_esc("-");
    }
    else {
        print_esc("discretionary");
    }
    break;
```
