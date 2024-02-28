# Section 127

Empirical tests show that the routine in this section performs a node-merging operation about 0.75 times per allocation, on the average, after which it finds that *r* $>$ *p + 1* about 95% of the time.

```c << Try to allocate within node |p| and its physical successors, and |goto found| if allocation was possible >>=
q = p + node_size(p); // find the physical successor
while(is_empty(q)) {
    // merge node |p| with node |q|
    t = rlink(q);
    if (q == rover) {
        rover = t;
    }
    llink(t) = llink(q);
    rlink(llink(q)) = t;
    q += node_size(q);
}
r = q - s;
if (r > p + 1) {
    // << Allocate from the top of node |p| and |goto found| >>
}
if (r == p && rlink(p) != p) {
    // << Allocate entire node |p| and |goto found| >>
}
node_size(p) = q - p; // reset the size in case it grew
```
