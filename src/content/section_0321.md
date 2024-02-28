# Section 321: Maintaining the input stacks

The following subroutines change the input status in commonly needed ways.

First comes *push_input*, which stores the current state and creates a new level (having, initially, the same properties as the old).

```c include/datastructures.h
// enter a new input level, save the old
#define push_input                                             \
    if (input_ptr > max_in_stack) {                            \
        max_in_stack = input_ptr;                              \
        if (input_ptr == STACK_SIZE) {                         \
            overflow("input stack size", STACK_SIZE);          \
        }                                                      \
    }                                                          \
    input_stack[input_ptr] = cur_input; /* stack the record */ \
    incr(input_ptr)
```
