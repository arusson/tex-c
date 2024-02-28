# Section 1053

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case STOP:
    if (chr_code == 1) {
        print_esc("dump");
    }
    else {
        print_esc("end");
    }
    break;
```
