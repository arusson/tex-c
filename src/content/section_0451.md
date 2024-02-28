# Section 451

The following code is executed when *scan_something_internal* was called asking for *MU_VAL*, when we really wanted a "mudimen" instead of "muglue".

```c << Coerce glue to a dimension >>=
if (cur_val_level >= GLUE_VAL) {
    v = width(cur_val);
    delete_glue_ref(cur_val);
    cur_val = v;
}
```
