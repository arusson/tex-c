# Section 311

The status at each level is indicated by printing two lines, where the first line indicates what was read so far and the second line shows what remains to be read.
The context is cropped, if necessary, so that the first line contains at most *HALF_ERROR_LINE* characters, and the second contains at most *ERROR_LINE*.
Non-current input levels whose *token_type* is *'BACKED_UP'* are shown only if they have not been fully read.

```c io/display_context.c
// << Start file |display_context.c| >>

// prints where the scanner is
void show_context() {
    int old_setting;  // saved |selector| setting
    int nn;           // number of contexts shown so far, less one
    bool bottom_line; // have we reached the final context to be shown?
    // << Local variables for formatting calculations >>
    
    base_ptr = input_ptr;
    input_stack[base_ptr] = cur_input; // store current state
    nn = -1;
    bottom_line = false;
    while(true) {
        cur_input = input_stack[base_ptr]; // enter into the context
        if (state != TOKEN_LIST
            && (name > 17 || base_ptr == 0))
        {
            bottom_line = true;
        }
        if (base_ptr == input_ptr
            || bottom_line
            || nn < error_context_lines)
        {
            // << Display the current context >>
        }
        else if (nn == error_context_lines) {
            print_nl("...");
            incr(nn); // omitted if |error_context_lines < 0|
        }
        if (bottom_line) {
            break; // Goto done
        }
        decr(base_ptr);
    }
    // done:
    cur_input = input_stack[input_ptr]; // restore original state
}
```
