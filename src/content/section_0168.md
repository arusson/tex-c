# Section 168

```c << Check single-word |avail| list >>=
p = avail;
q = null;
while (p != null) {
    if (p > mem_end
        || p < hi_mem_min
        || free_cells[p])
    {
        print_nl("AVAIL list clobbered at ");
        print_int(q);
        break; // Goto done1
    }
    free_cells[p] = true;
    q = p;
    p = link(q);
}
// done1:
```
