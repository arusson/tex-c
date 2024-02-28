# Section 429

When a *GLUE_VAL* changes to a *DIMEN_VAL*, we use the width component of the glue; there is no need to decrease the reference count, since it has not yet been increased.
When a *DIMEN_VAL* changes to an *INT_VAL*, we use scaled points so that the value doesn't actually change.
And when a *MU_VAL* changes to a *GLUE_VAL*, the value doesn't change either.

```c << Convert |cur_val| to a lower level >>=
if (cur_val_level == GLUE_VAL) {
    cur_val = width(cur_val);
}
else if (cur_val_level == MU_VAL) {
    mu_error();
}
decr(cur_val_level);
```
