# Section 1189

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case LEFT_RIGHT:
    if (chr_code == LEFT_NOAD) {
        print_esc("left");
    }
    else {
        print_esc("right");
    }
    break;
```
