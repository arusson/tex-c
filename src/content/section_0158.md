# Section 158

Anyone who has been reading the last few sections of the program will be able to guess what comes next.

```c datastructures/nodes.c
pointer new_penalty(int m) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = PENALTY_NODE;
    subtype(p) = 0; // the |subtype| is not used
    penalty(p) = m;
    return p;
}
```
