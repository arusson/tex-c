# Section 1009

We take note of the value of `\skip` *n* and the height plus depth of `\box`&nbsp;*n* only when the first `\insert`&nbsp;*n* node is encountered for a new page.
A user who changes the contents of `\box`&nbsp;*n* after that first `\insert`&nbsp;*n* had better be either extremely careful or extremely lucky, or both.

```c << Create a page insertion node with |subtype(r) = n|, and include the glue correction for box |n| in the current page state >>=
q = get_node(PAGE_INS_NODE_SIZE);
link(q) = link(r);
link(r) = q;
r = q;
subtype(r) = n;
type(r) = INSERTING;
ensure_vbox(n);
if (box(n) == null) {
    height(r) = 0;
}
else {
    height(r) = height(box(n)) + depth(box(n));
}
best_ins_ptr(r) = null;
q = skip(n);
if (count(n) == 1000) {
    h = height(r);
}
else {
    h = x_over_n(height(r), 1000)*count(n);
}
page_goal -= h + width(q);
page_so_far[2 + stretch_order(q)] += stretch(q);
page_shrink += shrink(q);
if (shrink_order(q) != NORMAL && shrink(q) != 0) {
    print_err("Infinite glue shrinkage inserted from ");
    print_esc("skip");
    print_int(n);
    help3("The correction glue for page breaking with insertions")
        ("must have finite shrinkability. But you may proceed,")
        ("since the offensive shrinkability has been made finite.");
    error();
}
```
