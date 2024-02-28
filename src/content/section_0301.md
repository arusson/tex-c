# Section 301

```c << Global variables >>+=
in_state_record input_stack[STACK_SIZE + 1];
int input_ptr;             // first unused location of |input_stack|
int max_in_stack;          // largest value of |input_ptr| when pushing
in_state_record cur_input; // the "top" input state, according to convention (1)
```
