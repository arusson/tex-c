# Section 1148

We need to be careful that *w*, *v*, and *d* do not depend on any *glue_set* values, since such values are subject to system-dependent rounding.
System-dependent numbers are not allowed to infiltrate parameters like *pre_display_size*, since $\TeX82$ is supposed to make the same decisions on all machines.

```c << Let |d| be the natural width of this glue; if stretching or shrinking, set |v = MAX_DIMEN|; |goto found| in the case of leaders >>=
q = glue_ptr(p);
d = width(q);
if (glue_sign(just_box) == STRETCHING) {
    if (glue_order(just_box) == stretch_order(q) && stretch(q) != 0) {
        v = MAX_DIMEN;
    }
}
else if (glue_sign(just_box) == SHRINKING) {
    if (glue_order(just_box) == shrink_order(q) && shrink(q) != 0) {
        v = MAX_DIMEN;
    }
}
if (subtype(p) >= A_LEADERS) {
    goto found;
}
```
