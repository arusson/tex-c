# Section 488

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case IF_TEST:
    switch (chr_code) {
    case IF_CAT_CODE:
        print_esc("ifcat");
        break;
    
    case IF_INT_CODE:
        print_esc("ifnum");
        break;
    
    case IF_DIM_CODE:
        print_esc("ifdim");
        break;
    
    case IF_ODD_CODE:
        print_esc("ifodd");
        break;
    
    case IF_VMODE_CODE:
        print_esc("ifvmode");
        break;
    
    case IF_HMODE_CODE:
        print_esc("ifhmode");
        break;
    
    case IF_MMODE_CODE:
        print_esc("ifmmode");
        break;
    
    case IF_INNER_CODE:
        print_esc("ifinner");
        break;
    
    case IF_VOID_CODE:
        print_esc("ifvoid");
        break;
    
    case IF_HBOX_CODE:
        print_esc("ifhbox");
        break;
    
    case IF_VBOX_CODE:
        print_esc("ifvbox");
        break;
    
    case IFX_CODE:
        print_esc("ifx");
        break;
    
    case IF_EOF_CODE:
        print_esc("ifeof");
        break;
    
    case IF_TRUE_CODE:
        print_esc("iftrue");
        break;
    
    case IF_FALSE_CODE:
        print_esc("iffalse");
        break;
    
    case IF_CASE_CODE:
        print_esc("ifcase");
        break;
    
    default:
        print_esc("if");
    } 
    break;
```
