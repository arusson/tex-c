# Section 399

```c << Contribute an entire group to the current parameter >>=
unbalance = 1;
while(true) {
    fast_store_new_token(cur_tok);
    get_token();
    if (cur_tok == par_token && long_state != LONG_CALL) {
        // << Report a runaway argument and abort >>
    }
    if (cur_tok < RIGHT_BRACE_LIMIT) {
        if (cur_tok < LEFT_BRACE_LIMIT) {
            incr(unbalance);
        }
        else {
            decr(unbalance);
            if (unbalance == 0) {
                goto done1;
            }
        }
    }
}
done1:
rbrace_ptr = p;
store_new_token(cur_tok);
```
