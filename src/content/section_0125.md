# Section 125

A call to *get_node* with argument *s* returns a pointer to a new node of size *s*, which must be 2 or more.
The *link* field of the first word of this new node is set to null.
An overflow stop occurs if no suitable space exists.

If *get_node* is called with $s = 2^{30}$, it simply merges adjacent free areas and returns the value *MAX_HALFWORD*.

```c datastructures/memory.c
// variable-size node allocation
pointer get_node(int s) {
    pointer p; // the node currently under inspection
    pointer q; // the node physically after node |p|
    int r;     // the newly allocated node, or a candidate for this honor
    int t;     // temporary register

restart:
    p = rover; // start at some free node in the ring
    do {
        // << Try to allocate within node |p| and its physical successors, and |goto found| if allocation was possible >>
        p = rlink(p); // move to the next node in the ring
    } while (p != rover); // repeat until the whole list has been traversed
    
    if (s == 0x40000000) {
        return MAX_HALFWORD;
    }
    if (lo_mem_max + 2 < hi_mem_min
        && lo_mem_max + 2 <= MEM_BOT + MAX_HALFWORD)
    {
        // << Grow more variable-size memory and |goto restart| >>
    }
    // sorry, nothing satisfactory is left
    overflow("main memory size", MEM_MAX + 1 - MEM_MIN);

found:
    link(r) = null; // this node is now nonempty
#ifdef STAT
    var_used += s; // maintain usage statistics
#endif
    return r;
}
```
