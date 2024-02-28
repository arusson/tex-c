# Section 1224

We temporarily define *p* to be *RELAX*, so that an occurrence of *p* while scanning the definition will simply stop the scanning instead of producing an "undefined control sequence" error or expanding the previous meaning.
This allows, for instance, '`\chardef\foo=123\foo`'.

```c << Assignments >>+=
case SHORTHAND_DEF:
    n = cur_chr;
    get_r_token();
    p = cur_cs;
    define(p, RELAX, 256);
    scan_optional_equals();
    switch (n) {
    case CHAR_DEF_CODE:
        scan_char_num();
        define(p, CHAR_GIVEN, cur_val);
        break;
  
    case MATH_CHAR_DEF_CODE:
        scan_fifteen_bit_int();
        define(p, MATH_GIVEN, cur_val);
        break;
  
    default:
        scan_eight_bit_int();
        switch (n) {
        case COUNT_DEF_CODE:
            define(p, ASSIGN_INT, COUNT_BASE + cur_val);
            break;
        case DIMEN_DEF_CODE:
            define(p, ASSIGN_DIMEN, SCALED_BASE + cur_val);
            break;
        case SKIP_DEF_CODE:
            define(p, ASSIGN_GLUE, SKIP_BASE + cur_val);
            break;
        case MU_SKIP_DEF_CODE:
            define(p, ASSIGN_MU_GLUE, MU_SKIP_BASE + cur_val);
            break;
        case TOKS_DEF_CODE:
            define(p, ASSIGN_TOKS, TOKS_BASE + cur_val);
        } // there are no other cases
    }
    break;
```
