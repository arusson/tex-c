# Section 827

```c << Get ready to start line breaking >>+=
no_shrink_error_yet = true;
check_shrinkage(left_skip);
check_shrinkage(right_skip);
q = left_skip;
r = right_skip;
background[1] = width(q) + width(r);
background[2] = 0;
background[3] = 0;
background[4] = 0;
background[5] = 0;
background[2 + stretch_order(q)] = stretch(q);
background[2 + stretch_order(r)] += stretch(r);
background[6] = shrink(q) + shrink(r);
```
