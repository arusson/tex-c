# Section 492

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case FI_OR_ELSE:
    if (chr_code == FI_CODE) {
        print_esc("fi");
    }
    else if (chr_code == OR_CODE) {
        print_esc("or");
    }
    else {
        print_esc("else");
    }
    break;
```
