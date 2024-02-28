# Section 322

And of course what goes up must come down.

```c include/datastructures.h
// leave an input level, re-enter the old
#define pop_input                      \
    decr(input_ptr);                   \
    cur_input = input_stack[input_ptr]
```
