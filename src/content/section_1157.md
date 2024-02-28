# Section 1157

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case MATH_COMP:
    switch (chr_code) {
    case ORD_NOAD:
        print_esc("mathord");
        break;
    
    case OP_NOAD:
        print_esc("mathop");
        break;
    
    case BIN_NOAD:
        print_esc("mathbin");
        break;

    case REL_NOAD:
        print_esc("mathrel");
        break;
    
    case OPEN_NOAD:
        print_esc("mathopen");
        break;
    
    case CLOSE_NOAD:
        print_esc("mathclose");
        break;
    
    case PUNCT_NOAD:
        print_esc("mathpunct");
        break;
    
    case INNER_NOAD:
        print_esc("mathinner");
        break;
    
    case UNDER_NOAD:
        print_esc("underline");
        break;
    
    default:
        print_esc("overline");
    }
    break;

case LIMIT_SWITCH:
    if (chr_code == LIMITS) {
        print_esc("limits");
    }
    else if (chr_code == NO_LIMITS) {
        print_esc("nolimits");
    }
    else {
        print_esc("displaylimits");
    }
    break;
```
