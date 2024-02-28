# Section 1110

```c builder/boxes_and_lists.c
void unpackage() {
    pointer p; // the box
    int c;     // should we copy?
    c = cur_chr;
    scan_eight_bit_int();
    p = box(cur_val);
    if (p == null) {
        return;
    }
    if (abs(mode) == MMODE
        || (abs(mode) == VMODE && type(p) != VLIST_NODE)
        || (abs(mode) == HMODE && type(p) != HLIST_NODE))
    {
        print_err("Incompatible list can't be unboxed");
        help3("Sorry, Pandora. (You sneaky devil.)")
            ("I refuse to unbox an \\hbox in vertical mode or vice versa.")
            ("And I can't open any boxes in math mode.");
        error();
        return;
    }
    if (c == COPY_CODE) {
        link(tail) = copy_node_list(list_ptr(p));
    }
    else {
        link(tail) = list_ptr(p);
        box(cur_val) = null;
        free_node(p, BOX_NODE_SIZE);
    }
    while (link(tail) != null) {
        tail = link(tail);
    }
}
```
