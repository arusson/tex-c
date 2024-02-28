# Section 167

Procedure *check_mem* makes sure that the available space lists of *mem* are well formed, and it optionally prints out all locations that are reserved now but were free the last time this procedure was called.

```c datastructures/memory.c
#ifdef DEBUG
void check_mem(bool print_locs) {
    pointer p, q;   // current locations of interest in |mem|
    bool clobbered; // is something amiss?
    for(p = MEM_MIN; p <= lo_mem_max; p++) {
        free_cells[p] = false; // you can probably do this faster
    }
    for(p = hi_mem_min; p <= mem_end; p++) {
        free_cells[p] = false; // ditto
    }
    // << Check single-word |avail| list >>
    // << Check variable-size |avail| list >>
    // << Check flags of unavailable nodes >>
    if (print_locs) {
        // << Print newly busy locations >>
    }
    for(p = MEM_MIN; p <= lo_mem_max; p++) {
        was_free[p] = free_cells[p];
    }
    for(p = hi_mem_min; p <= mem_end; p++) {
        was_free[p] = free_cells[p];
    }
    was_mem_end = mem_end;
    was_lo_max = lo_mem_max;
    was_hi_min = hi_mem_min;
}
#endif
```
