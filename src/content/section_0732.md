# Section 732

Conditional math glue ('`\nonscript`') results in a *GLUE_NODE* pointing to *ZERO_GLUE*, with *subtype(q) = COND_MATH_GLUE*; in such a case the node following will be eliminated if it is a glue or kern node and if the current size is different from *TEXT_SIZE*.
Unconditional math glue ('`\muskip`') is converted to normal glue by multiplying the dimensions by *cur_mu*.

```c << Convert math glue to ordinary glue >>=
if (subtype(q) == MU_GLUE) {
    x = glue_ptr(q);
    y = math_glue(x, cur_mu);
    delete_glue_ref(x);
    glue_ptr(q) = y;
    subtype(q) = NORMAL;
}
else if (cur_size != TEXT_SIZE && subtype(q) == COND_MATH_GLUE) {
    p = link(q);
    if (p != null
        && (type(p) == GLUE_NODE || type(p) == KERN_NODE))
    {
        link(q) = link(p);
        link(p) = null;
        flush_node_list(p);
    }
}
```
