# Section 973

```c << Use node |p| to update the current height and depth measurements; if this node is not a legal breakpoint, |goto not_found| or |update_heights|, otherwise set |pi| to the associated penalty at the break >>=
switch (type(p)) {
case HLIST_NODE:
case VLIST_NODE:
case RULE_NODE: 
    cur_height += prev_dp + height(p);
    prev_dp = depth(p);
    goto not_found;

case WHATSIT_NODE:
    // << Process whatsit |p| in |vert_break| loop, |goto not_found| >>

case GLUE_NODE:
    if (precedes_break(prev_p)) {
        pi = 0;
    }
    else {
        goto update_heights;
    }
    break;

case KERN_NODE:
    if (link(p) == null) {
        t = PENALTY_NODE;
    }
    else {
        t = type(link(p));
    }
    if (t == GLUE_NODE) {
        pi = 0;
    }
    else {
        goto update_heights;
    }
    break;

case PENALTY_NODE:
    pi = penalty(p);
    break;

case MARK_NODE:
case INS_NODE:
    goto not_found;

default:
    confusion("vertbreak");
}
```
