# Section 1311

By sorting the list of available spaces in the variable-size portion of *mem*, we are usually able to get by without having to dump very much of the dynamic memory.

We recompute *var_used* and *dyn_used*, so that `INITEX` dumps valid information even when it has not been gathering statistics.

```c << Dump the dynamic memory >>=
sort_avail();
var_used = 0;
dump_int(lo_mem_max);
dump_int(rover);
p = MEM_BOT;
q = rover;
x = 0;
do {
    for(k = p; k <= q + 1; k++) {
        dump_wd(mem[k]);
    }
    x =+ q + 2 - p;
    var_used += q - p;
    p = q + node_size(q);
    q = rlink(q);
} while (q != rover);
var_used += lo_mem_max - p;
dyn_used = mem_end + 1 - hi_mem_min;
for(k = p; k <= lo_mem_max; k++) {
    dump_wd(mem[k]);
}
x += lo_mem_max + 1 - p;
dump_int(hi_mem_min);
dump_int(avail);
for(k = hi_mem_min; k <= mem_end; k++) {
    dump_wd(mem[k]);
}
x += mem_end + 1 - hi_mem_min;
p = avail;
while (p != null) {
    decr(dyn_used);
    p = link(p);
}
dump_int(var_used);
dump_int(dyn_used);
print_ln();
print_int(x);
print(" memory locations dumped; current usage is ");
print_int(var_used);
print_char('&');
print_int(dyn_used);
```
