# Section 136

The *new_null_box* function returns a pointer to an *HLIST_NODE* in which all subfields have the values corresponding to '`\hbox{}`'.
(The *subtype* field is set to *MIN_QUARTERWORD*, for historic reasons that are no longer relevant.)

```c datastructures/nodes.c
// << Start file |nodes.c| >>

// creates a new box node
pointer new_null_box() {
    pointer p = get_node(BOX_NODE_SIZE); // the new node
    type(p) = HLIST_NODE;
    subtype(p) = MIN_QUARTERWORD;
    width(p) = 0;
    depth(p) = 0;
    height(p) = 0;
    shift_amount(p) = 0;
    list_ptr(p) = null;
    glue_sign(p) = NORMAL;
    glue_order(p) = NORMAL;
    set_glue_ratio_zero(glue_set(p));
    return p;
}
```
