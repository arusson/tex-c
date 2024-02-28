# Section 623

```c << Output a box in an hlist >>=
if (list_ptr(p) == null) {
    cur_h += width(p);
}
else {
    save_h = dvi_h;
    save_v = dvi_v;
    cur_v = base_line + shift_amount(p); // shift the box down
    temp_ptr = p;
    edge = cur_h;
    if (type(p) == VLIST_NODE) {
        vlist_out();
    }
    else {
        hlist_out();
    }
    dvi_h = save_h;
    dvi_v = save_v;
    cur_h = edge + width(p);
    cur_v = base_line;
}
```
