# Section 273

The following macro is used to test if there is room for up to six more entries on *save_stack*. By making a conservative test like this, we can get by with testing for overflow in only a few places.

```c include/datastructures.h
#define check_full_save_stack                     \
    do {                                          \
        if (save_ptr > max_save_stack) {          \
            max_save_stack = save_ptr;            \
            if (max_save_stack > SAVE_SIZE - 6) { \
                overflow("save size", SAVE_SIZE); \
            }                                     \
        }                                         \
    } while (0)
```
