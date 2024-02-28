# Section 282

```c << Clear off top level from |save_stack| >>=
while(true) {
    decr(save_ptr);
    if (save_type(save_ptr) == LEVEL_BOUNDARY) {
        break; // Goto done
    }
    p = save_index(save_ptr);
    if (save_type(save_ptr) == INSERT_TOKEN) {
        // << Insert token |p| into TeX's input >>
    }
    else {
        if (save_type(save_ptr) == RESTORE_OLD_VALUE) {
            l = save_level(save_ptr);
            decr(save_ptr);
        }
        else {
            save_stack[save_ptr] = eqtb[UNDEFINED_CONTROL_SEQUENCE];
        }
        // << Store |save_stack[save_ptr]| in |eqtb[p]|, unless |eqtb[p]| holds a global value >>
    }
}
// done:
cur_group = save_level(save_ptr);
cur_boundary = save_index(save_ptr);
```
