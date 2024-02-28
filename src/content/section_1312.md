# Section 1312

> ![NOTE]
> A part of the code has been removed since the condition is never true in this implementation.

```c << Undump the dynamic memory >>=
undump(LO_MEM_STAT_MAX + 1000, HI_MEM_STAT_MIN - 1, lo_mem_max);
undump(LO_MEM_STAT_MAX + 1, lo_mem_max, rover);
p = MEM_BOT;
q = rover;
do {
    for(k = p; k <= q + 1; k++) {
        undump_wd(mem[k]);
    }
    p = q + node_size(q);
    if (p > lo_mem_max ||
        (q >= rlink(q) && rlink(q) != rover))
    {
        goto bad_fmt;
    }
    q = rlink(q);
} while (q != rover);
for(k = p; k <= lo_mem_max; k++) {
    undump_wd(mem[k]);
}
/* This condition is never true in this implementation
if (MEM_MIN < MEM_BOT - 2) {
    // make more low memory available
    p = llink(rover);
    q = MEM_MIN + 1;
    link(MEM_MIN) = null;
    info(MEM_MIN) = null; // we don't use the bottom word
    rlink(p) = q;
    llink(rover) = q;
    rlink(q) = rover;
    llink(q) = p;
    link(q) = EMPTY_FLAG;
    node_size(q) = MEM_BOT - q;
} */
undump(lo_mem_max + 1, HI_MEM_STAT_MIN, hi_mem_min);
undump(null, MEM_TOP, avail);
mem_end = MEM_TOP;
for(k = hi_mem_min; k <= mem_end; k++) {
    undump_wd(mem[k]);
}
undump_int(var_used);
undump_int(dyn_used);
```
