# Section 803

Merging of two span-node lists is a typical exercise in the manipulation of linearly linked data structures.
The essential invariant in the following **repeat** loop is that we want to dispense with node *r*, in *q*'s list, and *u* is its successor; all nodes of *p*'s list up to and including *s* have been processed, and the successor of *s* matches *r* or precedes *r* or follows *r*, according as *link(r) = n* or *link(r)* $>$ *n* or *link(r)* $<$&nbsp;*n*.

```c << Merge the widths in the span nodes of |q| with those of |p|, destroying the span nodes of |q| >>=
t = width(q) + width(glue_ptr(link(q)));
r = info(q);
s = END_SPAN;
info(s) = p;
n = MIN_QUARTERWORD + 1;
do {
    width(r) -= t;
    u = info(r);
    while (link(r) > n) {
        s = info(s);
        n = link(info(s)) + 1;
    }
    if (link(r) < n) {
        info(r) = info(s);
        info(s) = r;
        decr(link(r));
        s = r;
    }
    else {
        if (width(r) > width(info(s))) {
            width(info(s)) = width(r);
        }
        free_node(r, SPAN_NODE_SIZE);
    }
    r = u;
} while (r != END_SPAN);
```
