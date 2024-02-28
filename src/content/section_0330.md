# Section 330

In order to keep the stack from overflowing during a long sequence of inserted '`\show`' commands, the following routine removes completed error-inserted lines from memory.

```c error.c
void clear_for_error_prompt() {
    while (state != TOKEN_LIST
        && terminal_input
        && input_ptr > 0
        && loc > limit)
    {
        end_file_reading();
    }
    print_ln();
    clear_terminal;
}
```
