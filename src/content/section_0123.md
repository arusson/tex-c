# Section 123

The procedure *flush_list(p)* frees an entire linked list of one-word nodes that starts at position *p*.

```c datastructures/memory.c
// makes list of single-word nodes
void flush_list(pointer p) {
    pointer q, r; // list traversers
    if (p != null) {
        r = p;
        do {
            q = r;
            r = link(r);
            decr_dyn_used;
        } while (r != null);
        // now |q| is the last node on the list
        link(q) = avail;
        avail = p;
    }
}
```
