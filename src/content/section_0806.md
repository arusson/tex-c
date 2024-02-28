# Section 806

```c << Make the running dimensions in rule |q| extend to the boundaries of the alignment >>=
if (is_running(width(q))) {
    width(q) = width(p);
}
if (is_running(height(q))) {
    height(q) = height(p);
}
if (is_running(depth(q))) {
    depth(q) = depth(p);
}
if (o != 0) {
    r = link(q);
    link(q) = null;
    q = hpack(q, NATURAL);
    shift_amount(q) = o;
    link(q) = r;
    link(s) = q;
}
```
