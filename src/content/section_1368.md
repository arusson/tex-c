# Section 1368

After all this preliminary shuffling, we come finally to the routines that actually send out the requested data.
Let's do `\special` first (it's easier).

```c << Declare procedures needed in |hlist_out|, |vlist_out| >>=
void special_out(pointer p) {
    int old_setting; // holds print |selector|
    int k;           // index into |str_pool|
    synch_h;
    synch_v;
    old_setting = selector;
    selector = NEW_STRING;
    show_token_list(link(write_tokens(p)), null, POOL_SIZE - pool_ptr);
    selector = old_setting;
    str_room(1);
    if (cur_length < 256) {
        dvi_out(XXX1);
        dvi_out(cur_length);
    }
    else {
        dvi_out(XXX4);
        dvi_four(cur_length);
    }
    for(k = str_start[str_ptr]; k <= pool_ptr - 1; k++) {
        dvi_out(str_pool[k]);
    }
    pool_ptr = str_start[str_ptr]; // erase the string
}
```
