# Section 189

```c << Display glue |p| >>=
if (subtype(p) >= A_LEADERS) {
    // << Display leaders |p| >>
}
else {
    print_esc("glue");
    if (subtype(p) != NORMAL) {
        print_char('(');
        if (subtype(p) < COND_MATH_GLUE) {
            print_skip_param(subtype(p) - 1);
        }
        else if (subtype(p) == COND_MATH_GLUE) {
            print_esc("nonscript");
        }
        else {
            print_esc("mskip");
        }
        print_char(')');
    }

    if (subtype(p) != COND_MATH_GLUE) {
        print_char(' ');
        if (subtype(p) < COND_MATH_GLUE) {
            print_spec(glue_ptr(p), "");
        }
        else {
            print_spec(glue_ptr(p), "mu");
        }
    }
}
```
