# Section 1130

We've now covered most of the abuses of `\halign` and `\valign`.
Let's take a look at what happens when they are used correctly.

```c << Cases of |main_control| that build boxes and lists >>+=
case VMODE + HALIGN:
case HMODE + VALIGN:
    init_align();
    break;

case MMODE + HALIGN:
    if (privileged()) {
        if (cur_group == MATH_SHIFT_GROUP) {
            init_align();
        }
        else {
            off_save();
        }
    }
    break;

case VMODE + ENDV:
case HMODE + ENDV:
    do_endv();
    break;
```
