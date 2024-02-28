# Section 170

```c << Check flags of unavailable nodes >>=
p = MEM_MIN;
while (p <= lo_mem_max) {
    // node |p| should not be empty
    if (is_empty(p)) {
        print_nl("Bad flag at ");
        print_int(p);
    }
    while (p <= lo_mem_max && !free_cells[p]) {
        incr(p);
    }
    while (p <= lo_mem_max && free_cells[p]) {
        incr(p);
    }
}
```
