# Section 412

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case REGISTER:
    if (chr_code == INT_VAL) {
        print_esc("count");
    }
    else if (chr_code == DIMEN_VAL) {
        print_esc("dimen");
    }
    else if (chr_code == GLUE_VAL) {
        print_esc("skip");
    }
    else {
        print_esc("muskip");
    }
    break;
```
