# Section 622

```c << Output the non-|CHAR_NODE| |p| for |hlist_out| and move to the next node >>=
switch (type(p)) {
case HLIST_NODE:
case VLIST_NODE:
    // << Output a box in an hlist >>
    break;

case RULE_NODE:
    rule_ht = height(p);
    rule_dp = depth(p);
    rule_wd = width(p);
    goto fin_rule;

case WHATSIT_NODE:
    // << Output the whatsit node |p| in an hlist >>
    break;

case GLUE_NODE:
    // << Move right or output leaders >>

case KERN_NODE:
case MATH_NODE:
    cur_h += width(p);
    break;

case LIGATURE_NODE:
    // << Make node |p| look like a |CHAR_NODE| and |goto reswitch| >>

default:
    do_nothing;
}
goto next_p;

fin_rule:
// << Output a rule in an hlist >>

move_past:
cur_h += rule_wd;

next_p:
p = link(p);
```
