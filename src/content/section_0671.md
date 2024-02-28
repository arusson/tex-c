# Section 671

```c << Incorporate glue into the vertical totals >>=
x += d;
d = 0;
g = glue_ptr(p);
x += width(g);
o = stretch_order(g);
total_stretch[o] += stretch(g);
o = shrink_order(g);
total_shrink[o] += shrink(g);
if (subtype(p) >= A_LEADERS) {
    g = leader_ptr(p);
    if (width(g) > w) {
        w = width(g);
    }
}
```
