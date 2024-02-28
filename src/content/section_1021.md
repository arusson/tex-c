# Section 1021

```c << Wrap up the box specified by node |r|, splitting node |p| if called for; set |wait = true| if node |p| holds a remainder after splitting >>=
if (type(r) == SPLIT_UP
    && broken_ins(r) == p
    && broken_ptr(r) != null)
{
    while (link(s) != broken_ptr(r)) {
        s = link(s);
    }
    link(s) = null;
    split_top_skip = split_top_ptr(p);
    ins_ptr(p) = prune_page_top(broken_ptr(r));
    if (ins_ptr(p) != null) {
        temp_ptr = vpack(ins_ptr(p), NATURAL);
        height(p) = height(temp_ptr) + depth(temp_ptr);
        free_node(temp_ptr, BOX_NODE_SIZE);
        wait = true;
    }
}
best_ins_ptr(r) = null;
n = subtype(r);
temp_ptr = list_ptr(box(n));
free_node(box(n), BOX_NODE_SIZE);
box(n) = vpack(temp_ptr, NATURAL);
```
