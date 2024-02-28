# Section 1142

When $\TeX$ is in display math mode, *cur_group = MATH_SHIFT_GROUP*, so it is not necessary for the *start_eq_no* procedure to test for this condition.

```c math/math_lists.c
void start_eq_no() {
    saved(0) = cur_chr;
    incr(save_ptr);
    // << Go into ordinary math mode >>
}
```
