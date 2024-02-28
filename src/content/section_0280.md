# Section 280

Subroutine *save_for_after* puts a token on the stack for save-keeping.

```c datastructures/stack.c
void save_for_after(halfword t) {
    if (cur_level > LEVEL_ONE) {
        check_full_save_stack;
        save_type(save_ptr) = INSERT_TOKEN;
        save_level(save_ptr) = LEVEL_ZERO;
        save_index(save_ptr) = t;
        incr(save_ptr);
    }
}
```
