# Section 1346

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case EXTENSION:
    switch (chr_code) {
    case OPEN_NODE:
        print_esc("openout");
        break;
    
    case WRITE_NODE:
        print_esc("write");
        break;
    
    case CLOSE_NODE:
        print_esc("closeout");
        break;
    
    case SPECIAL_NODE:
        print_esc("special");
        break;
    
    case IMMEDIATE_CODE:
        print_esc("immediate");
        break;
    
    case SET_LANGUAGE_CODE:
        print_esc("setlanguage");
        break;
    
    default:
        print("[unknown extension!]");
    }
    break;
```
