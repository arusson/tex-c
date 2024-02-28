# Section 324

When a token list has been fully scanned, the following computations should be done as we leave that level of input.
The *token_type* tends to be equal to either *BACKED_UP* or *INSERTED* about 2/3 of the time.

```c datastructures/stack.c
// leave a token-list input level
void end_token_list() {
    if (token_type >= BACKED_UP) {
        // token list to be deleted
        if (token_type <= INSERTED) {
            flush_list(start);
        }
        else {
            // update reference count
            delete_token_ref(start);
            if (token_type == MACRO) {
                // parameters must be flushed
                while (param_ptr > param_start) {
                    decr(param_ptr);
                    flush_list(param_stack[param_ptr]);
                }
            }
        }
    }
    else if (token_type == U_TEMPLATE) {
        if (align_state > 500000) {
            align_state = 0;
        }
        else {
            fatal_error("(interwoven alignment preambles are not allowed)");
        }
    }
    pop_input;
    check_interrupt;
}
```
