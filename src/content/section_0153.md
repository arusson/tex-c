# Section 153

Glue nodes that are more or less anonymous are created by *new_glue*, whose argument points to a glue specification.

```c datastructures/nodes.c
pointer new_glue(halfword q) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = GLUE_NODE;
    subtype(p) = NORMAL;
    leader_ptr(p) = null;
    glue_ptr(p) = q;
    incr(glue_ref_count(q));
    return p;
}
```
