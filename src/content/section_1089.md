# Section 1089

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case START_PAR:
    if (chr_code == 0) {
        print_esc("noindent");
    }
    else {
        print_esc("indent");
    }
    break;
```
