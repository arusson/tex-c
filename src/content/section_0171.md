# Section 171

```c << Print newly busy locations >>=
print_nl("New busy locs:");
for(p = MEM_MIN;  p <= lo_mem_max; p++) {
    if (!free_cells[p]
        && (p > was_lo_max || was_free[p]))
    {
        print_char(' ');
        print_int(p);
    }
}
for(p = hi_mem_min; p <= mem_end; p++) {
    if (!free_cells[p] && (p < was_hi_min
        || p > was_mem_end
        || was_free[p]))
    {
        print_char(' ');
        print_int(p);
    }
}
```
