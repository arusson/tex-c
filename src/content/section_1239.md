# Section 1239

```c << Compute the sum of two glue specs >>=
q = new_spec(cur_val);
r = equiv(l);
delete_glue_ref(cur_val);
width(q) += width(r);
if (stretch(q) == 0) {
    stretch_order(q) = NORMAL;
}
if (stretch_order(q) == stretch_order(r)) {
    stretch(q) += stretch(r);
}
else if (stretch_order(q) < stretch_order(r) && stretch(r) != 0) {
    stretch(q) = stretch(r);
    stretch_order(q) = stretch_order(r);
}
if (shrink(q) == 0) {
    shrink_order(q) = NORMAL;
}
if (shrink_order(q) == shrink_order(r)) {
    shrink(q) += shrink(r);
}
else if (shrink_order(q) < shrink_order(r) && shrink(r) != 0) {
    shrink(q) = shrink(r);
    shrink_order(q) = shrink_order(r);
}
cur_val = q;
```
