# Section 308

The *param_stack* is an auxiliary array used to hold pointers to the token lists for parameters at the current level and subsidiary levels of input.
This stack is maintained with convention (2), and it grows at a different rate from the others.

```c << Global variables >>+=
pointer param_stack[PARAM_SIZE + 1]; // token list pointers for parameters
int param_ptr;                       // first unused entry in |param_stack|
int max_param_stack;                 // largest value of |param_ptr|, will be |<= PARAM_SIZE + 9|
```
