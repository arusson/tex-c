# Section 464: Building token lists

The token lists for macros and for other things like `\mark` and `\output` and `\write` are produced by a procedure called *scan_toks*.

Before we get into the details of *scan_toks*, let's consider a much simpler task, that of converting the current string into a token list.
The *str_toks* function does this; it classifies spaces as type *SPACER* and everything else as type *OTHER_CHAR*.

The token list created by *str_toks* begins at *link(TEMP_HEAD)* and ends at the value *p* that is returned.
(If *p = TEMP_HEAD*, the list is empty.)

```c parser/build_tokens.c
// << Start file |build_tokens.c| >>

// converts |str_pool[b .. pool_ptr - 1]| to a token list
pointer str_toks(pool_pointer b) {
    pointer p;      // tail of the token list
    pointer q;      // new node being added to the token list via |store_new_token|
    halfword t;     // token being appended
    pool_pointer k; // index into |str_pool|
    str_room(1);
    p = TEMP_HEAD;
    link(p) = null;
    k = b;
    while (k < pool_ptr) {
        t = str_pool[k];
        if (t == ' ') {
            t = SPACE_TOKEN;
        }
        else {
            t = OTHER_TOKEN + t;
        }
        fast_store_new_token(t);
        incr(k);
    }
    pool_ptr = b;
    return p;
}
```
