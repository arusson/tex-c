# Section 430

If *cur_val* points to a glue specification at this point, the reference count for the glue does not yet include the reference by *cur_val*.
If *negative* is *true*, *cur_val_level* is known to be $\leq$ *MU_VAL*.

```c << Fix the reference count, if any, and negate |cur_val| if |negative| >>=
if (negative) {
    if (cur_val_level >= GLUE_VAL) {
        cur_val = new_spec(cur_val);
        // << Negate all three glue components of |cur_val| >>
    }
    else {
        negate(cur_val);
    }
}
else if (cur_val_level >= GLUE_VAL && cur_val_level <= MU_VAL) {
    add_glue_ref(cur_val);
}
```
