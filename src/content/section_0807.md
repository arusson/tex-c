# Section 807

The unset box *q* represents a row that contains one or more unset boxes, depending on how soon `\cr` occurred in that row.

```c << Set the unset box |q| and the unset boxes in it >>=
if (mode == -VMODE) {
    type(q) = HLIST_NODE;
    width(q) = width(p);
}
else {
    type(q) = VLIST_NODE;
    height(q) = height(p);
}
glue_order(q) = glue_order(p);
glue_sign(q) = glue_sign(p);
glue_set(q) = glue_set(p);
shift_amount(q) = o;
r = link(list_ptr(q));
s = link(list_ptr(p));
do {
    // << Set the glue in node |r| and change it from an unset node >>
    r = link(link(r));
    s = link(link(s));
} while (r != null);
```
