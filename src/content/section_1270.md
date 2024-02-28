# Section 1270

Here is a procedure that might be called 'Get the next non-blank non-relax non-call non-assignment token'.

```c builder/independent.c
void do_assignments() {
    while(true) {
        // << Get the next non-blank non-relax non-call token >>
        if (cur_cmd <= MAX_NON_PREFIXED_COMMAND) {
            return;
        }
        set_box_allowed = false;
        prefixed_command();
        set_box_allowed = true;
    }
}
```
