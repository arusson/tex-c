# Section 655

Although node *q* is not necessarily the immediate predecessor of node *p*, it always points to some node in the list preceding *p*.
Thus, we can delete nodes by moving *q* when necessary.
The algorithm takes linear time, and the extra computation does not intrude on the inner loop unless it is necessary to make a deletion.

```c << Transfer node |p| to the adjustment list >>=
while (link(q) != p) {
    q = link(q);
}
if (type(p) == ADJUST_NODE) {
    link(adjust_tail) = adjust_ptr(p);
    while (link(adjust_tail) != null) {
        adjust_tail = link(adjust_tail);
    }
    p = link(p);
    free_node(link(q), SMALL_NODE_SIZE);
}
else {
    link(adjust_tail) = p;
    adjust_tail = p;
    p = link(p);
}
link(q) = p;
p = q;
```
