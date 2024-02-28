# Section 151

Here is a function that returns a pointer to a copy of a glue spec.
The reference count in the copy is *null*, because there is assumed to be exactly one reference to the new specification.

```c datastructures/nodes.c
// duplicates a glue specification
pointer new_spec(pointer p) {
    pointer q = get_node(GLUE_SPEC_SIZE); // the new spec
    mem[q] = mem[p];
    glue_ref_count(q) = null;
    width(q) = width(p);
    stretch(q) = stretch(p);
    shrink(q) = shrink(p);
    return q;
}
```
