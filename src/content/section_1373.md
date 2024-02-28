# Section 1373

The *out_what* procedure takes care of outputting whatsit nodes for *vlist_out* and *hlist_out*.

```c << Declare procedures needed in |hlist_out|, |vlist_out| >>+=
void out_what(pointer p) {
    small_number j; // write stream number
    switch (subtype(p)) {
    case OPEN_NODE:
    case WRITE_NODE:
    case CLOSE_NODE:
        // << Do some work that has been queued up for \write >>
        break;
    
    case SPECIAL_NODE:
        special_out(p);
        break;
    
    case LANGUAGE_NODE:
        do_nothing;
        break;
    
    default:
        confusion("ext4");
    }
}
```
