# Section 1263

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case SET_INTERACTION:
    switch (chr_code) {
    case BATCH_MODE:
        print_esc("batchmode");
        break;
  
    case NONSTOP_MODE:
        print_esc("nonstopmode");
        break;
    
    case SCROLL_MODE:
        print_esc("scrollmode");
        break;
    
    default:
        print_esc("errorstopmode");
    }
    break;
```
