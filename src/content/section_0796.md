# Section 796

```c << Package an unset box for the current column and record its width >>=
if (mode == -HMODE) {
    adjust_tail = cur_tail;
    u = hpack(link(head), NATURAL);
    w = width(u);
    cur_tail = adjust_tail;
    adjust_tail = null;
}
else {
    u = vpackage(link(head), NATURAL, 0);
    w = height(u);
}
n = MIN_QUARTERWORD; // this represents a span count of 1
if (cur_span != cur_align) {
    // << Update width entry for spanned columns >>
}
else if (w > width(cur_align)) {
    width(cur_align) = w;
}
type(u) = UNSET_NODE;
span_count(u) = n;
// << Determine the stretch order >>
glue_order(u) = o;
glue_stretch(u) = total_stretch[o];
// << Determine the shrink order >>
glue_sign(u) = o;
glue_shrink(u) = total_shrink[o];
pop_nest();
link(tail) = u;
tail = u;
```
