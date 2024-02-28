# Section 1090

```c << Cases of |main_control| that build boxes and lists >>+=
case VMODE + START_PAR:
    new_graf(cur_chr > 0);
    break;

case VMODE + LETTER:
case VMODE + OTHER_CHAR:
case VMODE + CHAR_NUM:
case VMODE + CHAR_GIVEN:
case VMODE + MATH_SHIFT:
case VMODE + UN_HBOX:
case VMODE + VRULE:
case VMODE + ACCENT:
case VMODE + DISCRETIONARY:
case VMODE + HSKIP:
case VMODE + VALIGN:
case VMODE + EX_SPACE:
case VMODE + NO_BOUNDARY:
    back_input();
    new_graf(true);
    break;
```
