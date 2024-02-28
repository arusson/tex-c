# Section 673

```c << Determine vertical glue stretch setting, then |return| or |goto common_ending| >>=
// << Determine the stretch order >>
glue_order(r) = o;
glue_sign(r) = STRETCHING;
if (total_stretch[o] != 0) {
    glue_set(r) = (double)x / total_stretch[o];
}
else {
    glue_sign(r) = NORMAL;
    set_glue_ratio_zero(glue_set(r)); // there's nothing to stretch
}
if (o == NORMAL && list_ptr(r) != null) {
    // << Report an underfull vbox and |goto common_ending|, if this box is sufficiently bad >>
}
return r;
```
