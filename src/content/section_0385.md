# Section 385

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case TOP_BOT_MARK:
    switch (chr_code) {
    case FIRST_MARK_CODE:
        print_esc("firstmark");
        break;
    
    case BOT_MARK_CODE:
        print_esc("botmark");
        break;
    
    case SPLIT_FIRST_MARK_CODE:
        print_esc("splitfirstmark");
        break;
    
    case SPLIT_BOT_MARK_CODE:
        print_esc("splitbotmark");
        break;
    
    default:
        print_esc("topmark");
    } 
    break;
```
