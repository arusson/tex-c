# Section 152

And here's a function that creates a glue node for a given parameter identified by its code number; for example, *new_param_glue(LINE_SKIP_CODE)* returns a pointer to a glue node for the current `\lineskip`.

```c datastructures/nodes.c
pointer new_param_glue(small_number n) {
    pointer p; // the new node
    pointer q; // the glue specification
    p = get_node(SMALL_NODE_SIZE);
    type(p) = GLUE_NODE;
    subtype(p) = n + 1;
    leader_ptr(p) = null;
    q = glue_par(n);
    glue_ptr(p) = q;
    incr(glue_ref_count(q));
    return p;
}
```
