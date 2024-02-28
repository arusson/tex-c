# Section 657

When we get to the present part of the program, *x* is the natural width of the box being packaged.

```c << Determine the value of |width(r)| and the appropriate glue setting; then |return| or |goto common_ending| >>=
if (m == ADDITIONAL) {
    w = x + w;
}
width(r) = w;
x = w - x; // now |x| is the excess to be made up
if (x == 0) {
    glue_sign(r) = NORMAL;
    glue_order(r) = NORMAL;
    set_glue_ratio_zero(glue_set(r));
    return r;
}
else if (x > 0) {
    // << Determine horizontal glue stretch setting, then |return| or |goto common_ending| >>
}
else {
    // << Determine horizontal glue shrink setting, then |return| or |goto common_ending| >>
}
```
