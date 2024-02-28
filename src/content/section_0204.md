# Section 204

The copying procedure copies words en masse without bothering to look at their individual fields.
If the node format changes---for example, if the size is altered, or if some link field is moved to another relative position---then this code may need to be changed too.

```c datastructures/memory.c
// makes a duplicate of the node list that starts at |p|
// and returns a pointer to the new list
pointer copy_node_list(pointer p) {
    pointer h;        // temporary head of copied list
    pointer q;        // previous position in new list
    pointer r = null; // current node being fabricated for new list
    int words;        // number of words remaining to be copied
    h = get_avail();
    q = h;
    while(p != null) {
        // << Make a copy of node |p| in node |r| >>
        link(q) = r;
        q = r;
        p = link(p);
    }
    link(q) = null;
    q = link(h);
    free_avail(h);
    return q;
}
```
