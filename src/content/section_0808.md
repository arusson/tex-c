# Section 808

A box made from spanned columns will be followed by tabskip glue nodes and by empty boxes as if there were no spanning.
This permits perfect alignment of subsequent entries, and it prevents values that depend on floating point arithmetic from entering into the dimensions of any boxes.

```c << Set the glue in node |r| and change it from an unset node >>=
n = span_count(r);
t = width(s);
w = t;
u = HOLD_HEAD;
while (n > MIN_QUARTERWORD) {
    decr(n);
    // << Append tabskip glue and an empty box to list |u|, and update |s| and |t| as the prototype nodes are passed >>
}
if (mode == -VMODE) {
    // << Make the unset node |r| into an |HLIST_NODE| of width |w|, setting the glue as if the width were |t| >>
}
else {
    // << Make the unset node |r| into a |VLIST_NODE| of height |w|, setting the glue as if the height were |t| >>
}
shift_amount(r) = 0;
if (u != HOLD_HEAD) {
    // append blank boxes to account for spanned nodes
    link(u) = link(r);
    link(r) = link(HOLD_HEAD);
    r = u;
}
```
