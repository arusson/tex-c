# Section 249

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case ASSIGN_DIMEN:
    if (chr_code < SCALED_BASE) {
        print_length_param(chr_code - DIMEN_BASE);
    }
    else {
        print_esc("dimen");
        print_int(chr_code - SCALED_BASE);
    }
    break;
```
