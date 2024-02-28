# Section 736

```c << Declare math construction procedures >>+=
void make_vcenter(pointer q) {
    pointer v;    // the box that should be centered vertically
    scaled delta; // its height plus depth
    v = info(nucleus(q));
    if (type(v) != VLIST_NODE) {
        confusion("vcenter");
    }
    delta = height(v) + depth(v);
    height(v) = axis_height(cur_size) + half(delta);
    depth(v) = delta - height(v);
}
```
