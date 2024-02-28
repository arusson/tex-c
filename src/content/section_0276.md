# Section 276

To save a value of *eqtb[p]* that was established at level *l*, we can use the following subroutine.

```c datastructures/stack.c
// saves |eqtb[p]|
void eq_save(pointer p, quarterword l) {
    check_full_save_stack;
    if (l == LEVEL_ZERO) {
        save_type(save_ptr) = RESTORE_ZERO;
    }
    else {
        save_stack[save_ptr] = eqtb[p];
        incr(save_ptr);
        save_type(save_ptr) = RESTORE_OLD_VALUE;
    }
    save_level(save_ptr) = l;
    save_index(save_ptr) = p;
    incr(save_ptr);
}
```
