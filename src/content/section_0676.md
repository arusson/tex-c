# Section 676

```c << Determine vertical glue shrink setting, then |return| or |goto common_ending| >>=
// << Determine the shrink order >>
glue_order(r) = o;
glue_sign(r) = SHRINKING;
if (total_shrink[o] != 0) {
    glue_set(r) = (double)(-x) / total_shrink[o];
}
else {
    glue_sign(r) = NORMAL;
    set_glue_ratio_zero(glue_set(r)); // there's nothing to shrink
}
if (total_shrink[o] < -x
    && o == NORMAL
    && list_ptr(r) != null)
{
    last_badness = 1000000;
    set_glue_ratio_one(glue_set(r)); // use the maximum shrinkage
    // << Report an overfull vbox and |goto common_ending|, if this box is sufficiently bad >>
}
else if (o == NORMAL && list_ptr(r) != null) {
    // << Report a tight vbox and |goto common_ending|, if this box is sufficiently bad >>
}
return r;
```
