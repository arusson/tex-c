# Section 883

```c << Destroy the |t| nodes following |q|, and make |r| point to the following node >>=
if (t == 0) {
    r = link(q);
}
else {
    r = q;
    while (t > 1) {
        r = link(r);
        decr(t);
    }
    s = link(r);
    r = link(s);
    link(s) = null;
    flush_node_list(link(q));
    replace_count(q) = 0;
}
```
