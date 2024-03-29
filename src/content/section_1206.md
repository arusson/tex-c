# Section 1206

When `\halign` appears in a display, the alignment routines operate essentially as they do in vertical mode.
Then the following program is activated, with *p* and *q* pointing to the beginning and end of the resulting list, and with *aux_save* holding the *prev_depth* value.

```c << Finish an alignment in a display >>=
do_assignments();
if (cur_cmd != MATH_SHIFT) {
    // << Pontificate about improper alignment in display >>
}
else {
    // << Check that another $ follows >>
}
pop_nest();
tail_append(new_penalty(pre_display_penalty));
tail_append(new_param_glue(ABOVE_DISPLAY_SKIP_CODE));
link(tail) = p;
if (p != null) {
    tail = q;
}
tail_append(new_penalty(post_display_penalty));
tail_append(new_param_glue(BELOW_DISPLAY_SKIP_CODE));
prev_depth = aux_save.sc;
resume_after_display();
```
