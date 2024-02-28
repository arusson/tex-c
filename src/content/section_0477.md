# Section 477

```c << Scan and build the body of the token list; |goto found| when finished >>=
unbalance = 1;
while(true) {
    if (xpand) {
        // << Expand the next part of the input >>
    }
    else {
        get_token();
    }
    if (cur_tok < RIGHT_BRACE_LIMIT) {
        if (cur_cmd < RIGHT_BRACE) {
            incr(unbalance);
        }
        else {
            decr(unbalance);
            if (unbalance == 0) {
                goto found;
            }
        }
    }
    else if (cur_cmd == MAC_PARAM && macro_def) {
        // << Look for parameter number or ## >>
    }
    store_new_token(cur_tok);
}
```
