# Section 879

Glue and penalty and kern and math nodes are deleted at the beginning of a line, except in the anomalous case that the node to be deleted is actually one of the chosen breakpoints.
Otherwise the pruning done here is designed to match the lookahead computation in *try_break*, where the *break_width* values are computed for non-discretionary  breakpoints.

```c << Prune unwanted nodes at the beginning of the next line >>=
r = TEMP_HEAD;
while(true) {
    q = link(r);
    if (q == cur_break(cur_p) // |cur_break(cur_p)| is the next breakpoint
        // now |q| cannot be |null|   
        || is_char_node(q)
        || non_discardable(q)
        || (type(q) == KERN_NODE && subtype(q) != EXPLICIT))
    {
        break; // goto done1
    }    
    r = q; // now |type(q) = GLUE_NODE|, |KERN_NODE|, |MATH_NODE|, or |PENALTY_NODE|
}
//done1:
if (r != TEMP_HEAD) {
    link(r) = null;
    flush_node_list(link(TEMP_HEAD));
    link(TEMP_HEAD) = q;
}
```
