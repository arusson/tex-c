# Section 968

A subroutine called *prune_page_top* takes a pointer to a vlist and returns a pointer to a modified vlist in which all glue, kern, and penalty nodes have been deleted before the first box or rule node.
However, the first box or rule is actually preceded by a newly created glue node designed so that the topmost baseline will be at distance *split_top_skip* from the top, whenever this is possible without backspacing.

In this routine and those that follow, we make use of the fact that a vertical list contains no character nodes, hence the *type* field exists for each node in the list.

```c breaker/page_break.c
// << Start file |page_break.c| >>

// adjust top after page break
pointer prune_page_top(pointer p) {
    pointer prev_p; // lags one step behind |p|
    pointer q;      // temporary variable for list manipulation
    prev_p = TEMP_HEAD;
    link(TEMP_HEAD) = p;
    while (p != null) {
        switch (type(p)) {
        case HLIST_NODE:
        case VLIST_NODE:
        case RULE_NODE:
            // << Insert glue for |split_top_skip| and set |p = null| >>
            break;
        
        case WHATSIT_NODE:
        case MARK_NODE:
        case INS_NODE:
            prev_p = p;
            p = link(prev_p);
            break;
        
        case GLUE_NODE:
        case KERN_NODE:
        case PENALTY_NODE:
            q = p;
            p = link(q);
            link(q) = null;
            link(prev_p) = p;
            flush_node_list(q);
            break;
        
        default:
            confusion("pruning");
        }
    }
    return link(TEMP_HEAD);
}
```
