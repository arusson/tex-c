# Section 227

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>=
case ASSIGN_GLUE:
case ASSIGN_MU_GLUE:
    if (chr_code < SKIP_BASE) {
        print_skip_param(chr_code - GLUE_BASE);
    }
    else if (chr_code < MU_SKIP_BASE) {
        print_esc("skip");
        print_int(chr_code - SKIP_BASE);
    }
    else {
        print_esc("muskip");
        print_int(chr_code - MU_SKIP_BASE);
    }
    break;
```
