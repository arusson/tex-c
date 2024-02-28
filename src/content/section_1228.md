# Section 1228

Similar routines are used to assign values to the numeric parameters.

```c << Assignments >>+=
case ASSIGN_INT:
    p = cur_chr;
    scan_optional_equals();
    scan_int();
    word_define(p, cur_val);
    break;

case ASSIGN_DIMEN:
    p = cur_chr;
    scan_optional_equals();
    scan_normal_dimen;
    word_define(p, cur_val);
    break;

case ASSIGN_GLUE:
case ASSIGN_MU_GLUE:
    p = cur_chr;
    n = cur_cmd;
    scan_optional_equals();
    if (n == ASSIGN_MU_GLUE) {
        scan_glue(MU_VAL);
    }
    else {
        scan_glue(GLUE_VAL);
    }
    trap_zero_glue();
    define(p, GLUE_REF, cur_val);
    break;
```
