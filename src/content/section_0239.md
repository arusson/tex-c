# Section 239

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case ASSIGN_INT:
    if (chr_code < COUNT_BASE) {
        print_param(chr_code - INT_BASE);
    }
    else {
        print_esc("count");
        print_int(chr_code - COUNT_BASE);
    }
    break;
```
