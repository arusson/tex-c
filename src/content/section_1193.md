# Section 1193

Here is the only way out of math mode.

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + MATH_SHIFT:
    if (cur_group == MATH_SHIFT_GROUP) {
        after_math();
    }
    else {
        off_save();
    }
    break;
```
