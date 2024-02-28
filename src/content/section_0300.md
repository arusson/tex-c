# Section 300: Input stacks and states

This implementation of $\TeX$ uses two different conventions for representing sequential stacks.

1. If there is frequent access to the top entry, and if the stack is essentially never empty, then the top entry is kept in a global variable (even better would be a machine register), and the other entries appear in the array *stack[0 .. (ptr − 1)]*.
For example, the semantic stack described above is handled this way, and so is the input stack that we are about to study.

2. If there is infrequent top access, the entire stack contents are in the array *stack[0 ..(ptr − 1)]*. For example, the *save_stack* is treated this way, as we have seen.

The state of $\TeX$'s input mechanism appears in the input stack, whose entries are records with six fields, called *state*, *index*, *start*, *loc*,
*limit*, and *name*.
This stack is maintained with convention&nbsp;(1), so it is declared in the following way:

```c << Types in the outer block >>+=
typedef struct {
    quarterword state_field;
    quarterword index_field;
    halfword start_field;
    halfword loc_field;
    halfword limit_field;
    halfword name_field;
} in_state_record;
```
