# Section 840

```c << Compute the discretionary |break_width| values >>=
t = replace_count(cur_p);
v = cur_p;
s = post_break(cur_p);
while (t > 0) {
    decr(t);
    v = link(v);
    // << Subtract the width of node |v| from |break_width| >>
}
while (s != null) {
    // << Add the width of node |s| to |break_width| >>
    s = link(s);
}
break_width[1] += disc_width;
if (post_break(cur_p) == null) {
    s = link(v); // nodes may be discardable after the break
}
```
