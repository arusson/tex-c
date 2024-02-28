# Section 1101

```c builder/boxes_and_lists.c
void make_mark() {
    pointer p; // new node
    p = scan_toks(false, true);
    p = get_node(SMALL_NODE_SIZE);
    type(p) = MARK_NODE;
    subtype(p) = 0; // the |subtype| is not used
    mark_ptr(p) = def_ref;
    link(tail) = p;
    tail = p;
}
```
