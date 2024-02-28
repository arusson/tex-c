# Section 721

Here we save memory space in a common case.

```c << Simplify a trivial box >>=
q = list_ptr(x);
if (is_char_node(q)) {
    r = link(q);
    if (r != null
        && link(r) == null
        && !is_char_node(r)
        && type(r) == KERN_NODE)
    {
        // unneeded italic correction
        free_node(r, SMALL_NODE_SIZE);
        link(q) = null;
    }
}
```
