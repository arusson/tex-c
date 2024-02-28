# Section 730

```c << Cases for nodes that can appear in an mlist, after which we |goto done_with_node| >>=
case STYLE_NODE:
    cur_style = subtype(q);
    // << Set up the values of |cur_size| and |cur_mu|, based on |cur_style| >>
    goto done_with_node;

case CHOICE_NODE:
    // << Change this node to a style node followed by the correct choice, then |goto done_with_node| >>

case INS_NODE:
case MARK_NODE:
case ADJUST_NODE:
case WHATSIT_NODE:
case PENALTY_NODE:
case DISC_NODE:
    goto done_with_node;

case RULE_NODE:
    if (height(q) > max_h) {
        max_h = height(q);
    }
    if (depth(q) > max_d) {
        max_d = depth(q);
    }
    goto done_with_node;

case GLUE_NODE:
    // << Convert math glue to ordinary glue >>
    goto done_with_node;

case KERN_NODE:
    math_kern(q, cur_mu);
    goto done_with_node;
```
