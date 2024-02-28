# Section 1278

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case MESSAGE:
    if (chr_code == 0) {
        print_esc("message");
    }
    else {
        print_esc("errmessage");
    }
    break;
```
