# Section 1127

```c error.c
void align_error() {
    if (abs(align_state) > 2) {
        // << Express consternation over the fact that no alignment is in progress >>
    }
    else {
        back_input();
        if (align_state < 0) {
            print_err("Missing { inserted");
            incr(align_state);
            cur_tok = LEFT_BRACE_TOKEN + '{';
        }
        else {
            print_err("Missing } inserted");
            decr(align_state);
            cur_tok = RIGHT_BRACE_TOKEN + '}';
        }
        help3("I've put in what seems to be necessary to fix")
            ("the current column of the current alignment.")
            ("Try to go on, since this might almost work.");
        ins_error();
    }
}
```
