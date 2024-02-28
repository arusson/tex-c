# Section 656

```c << Incorporate glue into the horizontal totals >>=
g = glue_ptr(p);
x += width(g);
o = stretch_order(g);
total_stretch[o] += stretch(g);
o = shrink_order(g);
total_shrink[o] += shrink(g);
if (subtype(p) >= A_LEADERS) {
    g = leader_ptr(p);
    if (height(g) > h) {
        h = height(g);
    }
    if (depth(g) > d) {
        d = depth(g);
    }
}
```
