# Section 469

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case CONVERT:
    switch (chr_code) {
    case NUMBER_CODE:
        print_esc("number");
        break;
    
    case ROMAN_NUMERAL_CODE:
        print_esc("romannumeral");
        break;
    
    case STRING_CODE:
        print_esc("string");
        break;
    
    case MEANING_CODE:
        print_esc("meaning");
        break;
    
    case FONT_NAME_CODE:
        print_esc("fontname");
        break;
    
    default:
        print_esc("jobname");
    }
    break;
```
