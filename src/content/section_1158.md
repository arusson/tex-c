# Section 1158

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + MATH_COMP:
    tail_append(new_noad());
    type(tail) = cur_chr;
    scan_math(nucleus(tail));
    break;

case MMODE + LIMIT_SWITCH:
    math_limit_switch();
    break;
```
