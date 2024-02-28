# Section 632

The *synch_v* here allows the `DVI` output to use one-byte commands for adjusting *v* in most cases, since the baselineskip distance will usually be constant.

```c << Output a box in a vlist >>=
if (list_ptr(p) == null) {
    cur_v += height(p) + depth(p);
}
else {
    cur_v += height(p);
    synch_v;
    save_h = dvi_h;
    save_v = dvi_v;
    cur_h = left_edge + shift_amount(p); // shift the box right
    temp_ptr = p;
    if (type(p) == VLIST_NODE) {
        vlist_out();
    }
    else {
        hlist_out();
    }
    dvi_h = save_h;
    dvi_v = save_v;
    cur_v = save_v + depth(p);
    cur_h = left_edge;
}
```
