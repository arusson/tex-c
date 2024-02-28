# Section 1086

```c builder/boxes_and_lists.c
void package(small_number c) {
    scaled h;  // height of box
    pointer p; // first node in a box
    scaled d;  // max depth
    d = box_max_depth;
    unsave();
    save_ptr -= 3;
    if (mode == -HMODE) {
        cur_box = hpack(link(head), saved(2), saved(1));
    }
    else {
        cur_box = vpackage(link(head), saved(2), saved(1), d);
        if (c == VTOP_CODE) {
            // << Readjust the height and depth of |cur_box|, for \vtop >>
        }
    }
    pop_nest();
    box_end(saved(0));
}
```
