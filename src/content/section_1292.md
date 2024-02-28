# Section 1292

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case XRAY:
    switch (chr_code) {
    case SHOW_BOX_CODE:
        print_esc("showbox");
        break;
    
    case SHOW_THE_CODE:
        print_esc("showthe");
        break;
    
    case SHOW_LISTS_CODE:
        print_esc("showlists");
        break;
    
    default:
        print_esc("show");
    }
    break;
```
