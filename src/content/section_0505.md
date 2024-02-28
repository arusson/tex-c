# Section 505

```c << Test box register status >>=
scan_eight_bit_int();
p = box(cur_val);
if (this_if == IF_VOID_CODE) {
    b = (p == null);
}
else if (p == null) {
    b = false;
}
else if (this_if == IF_HBOX_CODE) {
    b = (type(p) == HLIST_NODE);
}
else {
    b = (type(p) == VLIST_NODE);
}
```
