# Section 1223

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case SHORTHAND_DEF:
    switch (chr_code) {
    case CHAR_DEF_CODE:
        print_esc("chardef");
        break;
    
    case MATH_CHAR_DEF_CODE:
        print_esc("mathchardef");
        break;
    
    case COUNT_DEF_CODE:
        print_esc("countdef");
        break;
    
    case DIMEN_DEF_CODE:
        print_esc("dimendef");
        break;
    
    case SKIP_DEF_CODE:
        print_esc("skipdef");
        break;
    
    case MU_SKIP_DEF_CODE:
        print_esc("muskipdef");
        break;
    
    default:
        print_esc("toksdef");
    }
    break;

case CHAR_GIVEN:
    print_esc("char");
    print_hex(chr_code); 
    break;

case MATH_GIVEN:
    print_esc("mathchar");
    print_hex(chr_code);
    break;
```
