# Section 327

The *back_error* routine is used when we want to replace an offending token just before issuing an error message.
This routine, like *back_input*, requires that *cur_tok* has been set.
We disable interrupts during the call of *back_input* so that the help message won't be lost.

```c datastructures/stack.c
// back up one token and call |error|
void back_error() {
    ok_to_interrupt = false;
    back_input();
    ok_to_interrupt = true;
    error();
}

// back up one inserted token and call |error|
void ins_error() {
    ok_to_interrupt = false;
    back_input();
    token_type = INSERTED;
    ok_to_interrupt = true;
    error();
}
```
