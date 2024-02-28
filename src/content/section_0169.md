# Section 169

```c << Check variable-size |avail| list >>=
p = rover;
q = null;
do {
    if (p >= lo_mem_max
        || p < MEM_MIN
        || rlink(p) >= lo_mem_max
        || rlink(p) < MEM_MIN
        || !is_empty(p)
        || node_size(p) < 2
        || p + node_size(p) > lo_mem_max
        || llink(rlink(p)) != p)
    {
        print_nl("Double-AVAIL list clobbered at ");
        print_int(q);
        goto done2;
    }
    for(q = p;  q < (p + node_size(p)); q++) {
        if (free_cells[q]) {
            print_nl("Doubly free location at ");
            print_int(q);
            goto done2;
        }
        free_cells[q] = true;
    }
    q = p;
    p = rlink(p);
} while (p != rover);
done2:
```
