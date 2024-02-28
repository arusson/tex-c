# Section 1370

```c << Declare procedures needed in |hlist_out|, |vlist_out| >>+=
void write_out(pointer p) {
    int old_setting; // holds print |selector|
    int old_mode;    // saved |mode|
    small_number j;  // write stream number
    pointer q, r;    // temporary variables for list manipulation
    
    // << Expand macros in the token list and make |link(def_ref)| point to the result >>
    old_setting = selector;
    j = write_stream(p);
    if (write_open[j]) {
        selector = j;
    }
    else {
        // write to the terminal if file isn't open
        if (j == 17 && selector == TERM_AND_LOG) {
            selector = LOG_ONLY;
        }
        print_nl("");
    }
    token_show(def_ref);
    print_ln();
    flush_list(def_ref);
    selector = old_setting;
}
```
