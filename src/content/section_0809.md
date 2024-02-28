# Section 809

```c << Append tabskip glue and an empty box to list |u|, and update |s| and |t| as the prototype nodes are passed >>=
s = link(s);
v = glue_ptr(s);
link(u) = new_glue(v);
u = link(u);
subtype(u) = TAB_SKIP_CODE + 1;
t += width(v);
if (glue_sign(p) == STRETCHING) {
    if (stretch_order(v) == glue_order(p)) {
        t += (scaled)round(glue_set(p)*stretch(v));
    }
}
else if (glue_sign(p) == SHRINKING) {
    if (shrink_order(v) == glue_order(p)) {
        t -= (scaled)round(glue_set(p)*shrink(v));
    }
}
s = link(s);
link(u) = new_null_box();
u = link(u);
t += width(s);
if (mode == -VMODE) {
    width(u) = width(s);
}
else {
    type(u) = VLIST_NODE;
    height(u) = width(s);
}
```
