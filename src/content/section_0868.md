# Section 868

When node *cur_p* is a glue node, we look at *prev_p* to see whether or not a breakpoint is legal at *cur_p*, as explained above.

```c << If node |cur_p| is a legal breakpoint, call |try_break|; then update the active widths by including the glue in |glue_ptr(cur_p)| >>=
if (auto_breaking) {
    if (is_char_node(prev_p)
        || precedes_break(prev_p)
        || (type(prev_p) == KERN_NODE && subtype(prev_p) != EXPLICIT))
    {
        try_break(0, UNHYPHENATED);
    }
}
check_shrinkage(glue_ptr(cur_p));
q = glue_ptr(cur_p);
act_width += width(q);
active_width[2 + stretch_order(q)] += stretch(q);
active_width[6] += shrink(q);
```
