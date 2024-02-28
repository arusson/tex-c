# Section 126

The lower part of *mem* grows by 1000 words at a time, unless we are very close to going under.
When it grows, we simply link a new node into the available-space list.
This method of controlled growth helps to keep the *mem* usage consecutive when $\TeX$ is implemented on "virtual memory" systems.

```c << Grow more variable-size memory and |goto restart| >>=
if (hi_mem_min - lo_mem_max >= 1998) {
    t = lo_mem_max + 1000;
}
else {
    // |lo_mem_max + 2 <= t < hi_mem_min|
    t = lo_mem_max + 1 + (hi_mem_min - lo_mem_max) / 2;
}
p = llink(rover);
q = lo_mem_max;
rlink(p) = q;
llink(rover) = q;

if (t > MEM_BOT + MAX_HALFWORD) {
    t = MEM_BOT + MAX_HALFWORD;
}
rlink(q) = rover;
llink(q) = p;
link(q) = EMPTY_FLAG;
node_size(q) = t - lo_mem_max;
lo_mem_max = t;
link(lo_mem_max) = null;
info(lo_mem_max) = null;
rover = q;
goto restart;
```
