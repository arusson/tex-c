# Section 293

```c << Display token |p|, and |return| if there are problems >>=
if ( p < hi_mem_min || p > mem_end) {
    print_esc("CLOBBERED.");
    return;
}
if (info(p) >= CS_TOKEN_FLAG) {
    print_cs(info(p) - CS_TOKEN_FLAG);
}
else {
    m = info(p) / 256;
    c = info(p) % 256;
    if (info(p) < 0) {
        print_esc("BAD.");
    }
    else {
        // << Display the token (|m|, |c|) >>
    }
}
```
