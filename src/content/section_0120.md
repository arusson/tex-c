# Section 120

The function *get_avail* returns a pointer to a new one-word node whose *link* field is null.
However, $\TeX$ will halt if there is no more room left.

If the available-space list is empty, i.e., if *avail = null*, we try first to increase *mem_end*.
If that cannot be done, i.e., if *mem_end = MEM_MAX*, we try to decrease *hi_mem_min*.
If that cannot be done, i.e., if *hi_mem_min = lo_mem_max + 1*, we have to quit.

```c datastructures/memory.c
// << Start file |memory.c| >>

// single-word node allocation
pointer get_avail() {
    pointer p; // the new node being got
    p = avail; // get top location in the |avail| stack
    if (p != null) {
        // and pop-it off
        avail = link(avail);
    }
    else if (mem_end < MEM_MAX) {
        // or go into virgin directory
        incr(mem_end);
        p = mem_end;
    }
    else {
        decr(hi_mem_min);
        p = hi_mem_min;
        if (hi_mem_min <= lo_mem_max) {
            // if memory is exhausted, display possible runaway text
            runaway();
            // quit; all one-word nodes are busy
            overflow("main memory size", MEM_MAX + 1 - MEM_MIN);
        }
    }
    link(p) = null; // provide an oft-desired initialization of the new node
    incr_dyn_used; // maintain statistics
    return p;
}
```
