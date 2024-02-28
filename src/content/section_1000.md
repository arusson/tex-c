# Section 1000

The title of this section is already so long, it seems best to avoid making it more accurate but still longer, by mentioning the fact that a kern node at the end of the contribution list will not be contributed until we know its successor.

```c << If the current page is empty and node |p| is to be deleted, |goto done1|; otherwise use node |p| to update the state of the current page; if this node is an insertion, |goto contribute|; otherwise if this node is not a legal breakpoint, |goto contribute| or |update_heights|; otherwise set |pi| to the penalty associated with this breakpoint >>=
switch (type(p)) {
case HLIST_NODE:
case VLIST_NODE:
case RULE_NODE:
    if (page_contents < BOX_THERE) {
        // << Initialize the current page, insert the \topskip glue ahead of |p|, and |goto continue| >>
    }
    else {
        // << Prepare to move a box or rule node to the current page, then |goto contribute| >>
    }
    break;

case WHATSIT_NODE:
    // << Prepare to move whatsit |p| to the current page, then |goto contribute| >>

case GLUE_NODE:
    if (page_contents < BOX_THERE) {
        goto done1;
    }
    else if (precedes_break(page_tail)) {
        pi = 0;
    }
    else {
        goto update_heights;
    }
    break;

case KERN_NODE:
    if (page_contents < BOX_THERE) {
        goto done1;
    }
    else if (link(p) == null) {
        return;
    }
    else if (type(link(p)) == GLUE_NODE) {
        pi = 0;
    }
    else {
        goto update_heights;
    }
    break;

case PENALTY_NODE:
    if (page_contents < BOX_THERE) {
        goto done1;
    }
    else {
        pi = penalty(p);
    }
    break;

case MARK_NODE:
    goto contribute;

case INS_NODE:
    // << Append an insertion to the current page and |goto contribute| >>

default:
    confusion("page");
}
```
