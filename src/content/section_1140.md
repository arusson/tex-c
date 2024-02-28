# Section 1140

We get into ordinary math mode from display math mode when '`\eqno`' or '`\leqno`' appears.
In such cases *cur_chr* will be 0 or&nbsp;1, respectively;
the value of *cur_chr* is placed onto *save_stack* for safe keeping.

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + EQ_NO:
    if (privileged()) {
        if (cur_group == MATH_SHIFT_GROUP) {
            start_eq_no();
        }
        else {
            off_save();
        }
    }
    break;
```
