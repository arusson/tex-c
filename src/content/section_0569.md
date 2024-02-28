# Section 569

```c << Read character data >>=
for(k = fmem_ptr; k <= width_base[f] - 1; k++) {
    store_four_quarters(font_info[k]);
    if ( a >= nw || b/16 >= nh || b % 16 >= nd || c/4 >= ni) {
        abort;
    }
    switch (c % 4) {
    case LIG_TAG:
        if (d >= nl) {
            abort;
        }
        break;
    
    case EXT_TAG:
        if (d >= ne) {
            abort;
        }
        break;
    
    case LIST_TAG:
        // << Check for charlist cycle >>
        break;
    
    default:
        do_nothing; // (|NO_TAG|)
    }
}
```
