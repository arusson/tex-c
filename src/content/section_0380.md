# Section 380

Here is a recursive procedure that is $\TeX$'s usual way to get the next token of input.
It has been slightly optimized to take account of common cases.

```c parser/expand_next_token.c
// sets |cur_cmd|, |cur_chr|, |cur_tok|, and expands macros
void get_x_token() {
    // restart:
    while(true) {
        get_next();
        if (cur_cmd <= MAX_COMMAND) {
            break; // Goto done
        }
        if (cur_cmd >= CALL) {
            if (cur_cmd < END_TEMPLATE) {
                macro_call();
            }
            else {
                cur_cs = FROZEN_ENDV;
                cur_cmd = ENDV;
                break; // Goto done; |cur_chr = NULL_LIST|
            }
        }
        else {
            expand();
        }
        // Goto restart
    }
    // done:
    if (cur_cs == 0) {
        cur_tok = (cur_cmd * 256) + cur_chr;
    }
    else {
        cur_tok = CS_TOKEN_FLAG + cur_cs;
    }
}
```
