# Section 1171

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + MATH_STYLE:
    tail_append(new_style(cur_chr));
    break;

case MMODE + NON_SCRIPT:
    tail_append(new_glue(ZERO_GLUE));
    subtype(tail) = COND_MATH_GLUE;
    break;

case MMODE + MATH_CHOICE:
    append_choices();
    break;
```
