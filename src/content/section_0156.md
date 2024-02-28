# Section 156

The *new_kern* function creates a kern node having a given width.

```c datastructures/nodes.c
pointer new_kern(scaled w) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = KERN_NODE;
    subtype(p) = NORMAL;
    width(p) = w;
    return p;
}
```
