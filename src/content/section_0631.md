# Section 631

```c << Output the non-|CHAR_NODE| |p| for |vlist_out| >>=
switch (type(p)) {
case HLIST_NODE:
case VLIST_NODE:
    // << Output a box in a vlist >>
    break;

case RULE_NODE:
    rule_ht = height(p);
    rule_dp = depth(p);
    rule_wd = width(p);
    goto fin_rule;

case WHATSIT_NODE:
    // << Output the whatsit node |p| in a vlist >>
    break;

case GLUE_NODE:
    // << Move down or output leaders >>

case KERN_NODE:
    cur_v += width(p);
    break;

default:
    do_nothing;
}
goto next_p;

fin_rule:
// << Output a rule in a vlist, |goto next_p| >>

move_past:
cur_v += rule_ht;
```
