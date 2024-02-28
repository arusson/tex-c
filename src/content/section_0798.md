# Section 798

```c << Update width entry for spanned columns >>=
q = cur_span;
do {
    incr(n);
    q = link(link(q));
} while (q != cur_align);
if (n > MAX_QUARTERWORD) {
    confusion("256 spans"); // this can happen, but won't
}
q = cur_span;
while (link(info(q)) < n) {
    q = info(q);
}
if (link(info(q)) > n) {
    s = get_node(SPAN_NODE_SIZE);
    info(s) = info(q);
    link(s) = n;
    info(q) = s;
    width(s) = w;
}
else if (width(info(q)) < w) {
    width(info(q)) = w;
}
```
