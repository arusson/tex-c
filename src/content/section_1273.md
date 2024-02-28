# Section 1273

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case IN_STREAM:
    if (chr_code == 0) {
        print_esc("closein");
    }
    else {
        print_esc("openin");
    }
    break;
```
