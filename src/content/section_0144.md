# Section 144

The *new_ligature* function creates a ligature node having given contents of the *font*, *character*, and *lig_ptr* fields.
We also have a *new_lig_item* function, which returns a two-word node having a given *character* field.
Such nodes are used for temporary processing as ligatures are being created.

```c datastructures/nodes.c
pointer new_ligature(quarterword f, quarterword c, pointer q) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = LIGATURE_NODE;
    font(lig_char(p)) = f;
    character(lig_char(p)) = c;
    lig_ptr(p) = q;
    subtype(p) = 0;
    return p;
}

pointer new_lig_item(quarterword c) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    character(p) = c;
    lig_ptr(p) = null;
    return p;
}
```
