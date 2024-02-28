# Section 482

The *read_toks* procedure constructs a token list like that for any macro definition, and makes *cur_val* point to it.
Parameter *r* points to the control sequence that will receive this token list.

```c parser/build_tokens.c
void read_toks(int n, pointer r) {
    pointer p;      // tail of the token list
    pointer q;      // new node being added to the token list via |store_new_token|
    int s;          // saved value of |align_state|
    small_number m; // stream number
    scanner_status = DEFINING;
    warning_index = r;
    def_ref = get_avail();
    token_ref_count(def_ref) = null;
    p = def_ref; // the reference count
    store_new_token(END_MATCH_TOKEN);
    if (n < 0 || n > 15) {
        m = 16;
    }
    else {
        m = n;
    }
    s = align_state;
    align_state = 1000000; // disable tab marks, etc.
    do {
        // << Input and store tokens from the next line of the file >>
    } while (align_state != 1000000);
    cur_val = def_ref;
    scanner_status = NORMAL;
    align_state = s;
}
```
