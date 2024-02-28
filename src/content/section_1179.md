# Section 1179

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case ABOVE:
    switch (chr_code) {
    case OVER_CODE:
        print_esc("over");
        break;
    
    case ATOP_CODE:
        print_esc("atop");
        break;
    
    case DELIMITED_CODE + ABOVE_CODE:
        print_esc("abovewithdelims");
        break;
    
    case DELIMITED_CODE + OVER_CODE:
        print_esc("overwithdelims");
        break;
    
    case DELIMITED_CODE + ATOP_CODE:
        print_esc("atopwithdelims");
        break;
    
    default:
        print_esc("above");
    }
    break;
```
