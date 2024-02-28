# Section 1022

```c << Either append the insertion node |p| after node |q|, and remove it from the current page, or delete |node(p)| >>=
link(prev_p) = link(p);
link(p) = null;
if (wait) {
    link(q) = p;
    q = p;
    incr(insert_penalties);
}
else {
    delete_glue_ref(split_top_ptr(p));
    free_node(p, INS_NODE_SIZE);
}
p = prev_p;
```
