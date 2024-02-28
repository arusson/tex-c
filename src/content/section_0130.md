# Section 130

Conversely, when some variable-size node *p* of size *s* is no longer needed, the operation *free_node(p, s)* will make its words available, by inserting *p* as a new empty node just before where *rover* now points.

```c datastructures/memory.c
// variable-size node liberation
void free_node(pointer p, halfword s) {
    pointer q; // |llink(rover)|
    // set both links
    node_size(p) = s;
    link(p) = EMPTY_FLAG;
    q = llink(rover);
    llink(p) = q;
    rlink(p) = rover;
    // insert |p| into the ring
    llink(rover) = p;
    rlink(q) = p;
#ifdef STAT
    var_used -= s; // maintain statistics
#endif
}
```
