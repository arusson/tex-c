# Section 325

Sometimes $\TeX$ has read too far and wants to "unscan" what it has seen.
The *back_input* procedure takes care of this by putting the token just scanned back into the input stream, ready to be read again.
This procedure can be used only if *cur_tok* represents the token to be replaced.
Some applications of $\TeX$ use this procedure a lot, so it has been slightly optimized for speed.

```c datastructures/stack.c
// undoes one token of input
void back_input() {
    pointer p; // a token list of length one
    while (state == TOKEN_LIST
        && loc == null
        && token_type != V_TEMPLATE)
    {
        // conserve stack space
        end_token_list();
    }
    p = get_avail();
    info(p) = cur_tok;
    if (cur_tok < RIGHT_BRACE_LIMIT) {
        if (cur_tok < LEFT_BRACE_LIMIT) {
            decr(align_state);
        }
        else {
            incr(align_state);
        }
    }
    push_input;
    state = TOKEN_LIST;
    start = p;
    token_type = BACKED_UP;
    loc = p; // that was |back_list(p)|, without procedure overhead
}
```
