# Section 172

The *search_mem* procedure attempts to answer the question "Who points to node *p*?"
In doing so, it fetches *link* and *info* fields of *mem* that might not be of type *two_halves*. Strictly speaking, this is undefined in Pascal, and it can lead to "false drops" (words that seem to point to *p* purely by coincidence).
But for debugging purposes, we want to rule out the places that do *not* point to *p*, so a few false drops are tolerable.

```c datastructures/memory.c
#ifdef DEBUG
// look for pointers to |p|
void search_mem(pointer p) {
    int q; // current position being searched
    for(q = MEM_MIN; q <= lo_mem_max; q++) {
        if (link(q) == p) {
            print_nl("LINK(");
            print_int(q);
            print_char(')');
        }
        if (info(q) == p) {
            print_nl("INFO(");
            print_int(q);
            print_char(')');
        }
    }
    for(q = hi_mem_min; q <= mem_end; q++) {
        if (link(q) == p) {
            print_nl("LINK(");
            print_int(q);
            print_char(')');
        }
        if (info(q) == p) {
            print_nl("INFO(");
            print_int(q);
            print_char(')');
        }
    }

    // << Search |eqtb| for equivalents equal to |p| >>
    // << Search |save_stack| for equivalents that point to |p| >>
    // << Search |hyph_list| for pointers to |p| >>
}
#endif
```
