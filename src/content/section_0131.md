# Section 131

Just before `INITEX` writes out the memory, it sorts the doubly linked available space list.
The list is probably very short at such times, so a simple insertion sort is used.
The smallest available location will be pointed to by *rover*, the next-smallest by *rlink(rover)*, etc.

```c datastructures/memory.c
#ifdef INIT
// sorts the available variable-size nodes by location
void sort_avail() {
    pointer p, q, r;   // indices into |mem|
    pointer old_rover; // initial |rover| setting
    p = get_node(0x40000000); // merge adjacent free areas
    p = rlink(rover);
    rlink(rover) = MAX_HALFWORD;
    old_rover = rover;
    while (p != old_rover) {
        // << Sort |p| into the list starting at |rover| and advance |p| to |rlink(p)| >>
    }
    p = rover;
    while (rlink(p) != MAX_HALFWORD) {
        llink(rlink(p)) = p;
        p = rlink(p);
    }
    rlink(p) = rover;
    llink(rover) = p;
}
#endif
```
