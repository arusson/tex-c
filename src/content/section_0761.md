# Section 761

Just before doing the big **case** switch in the second pass, the program sets up default values so that most of the branches are short.

```c << If node |q| is a style node, change the style and |goto delete_q|; otherwise if it is not a noad, put it into the hlist, advance |q|, and |goto done|; otherwise set |s| to the size of noad |q|, set |t| to the associated type (|ORD_NOAD .. INNER_NOAD|), and set |pen| to the associated penalty >>=
t = ORD_NOAD;
s = NOAD_SIZE;
pen = INF_PENALTY;
switch (type(q)) {
case OP_NOAD:
case OPEN_NOAD:
case CLOSE_NOAD:
case PUNCT_NOAD:
case INNER_NOAD:
    t = type(q);
    break;

case BIN_NOAD:
    t = BIN_NOAD;
    pen = bin_op_penalty;
    break;

case REL_NOAD:
    t = REL_NOAD;
    pen = rel_penalty;
    break;

case ORD_NOAD:
case VCENTER_NOAD:
case OVER_NOAD:
case UNDER_NOAD:
    do_nothing;
    break;

case RADICAL_NOAD:
    s = RADICAL_NOAD_SIZE;
    break;

case ACCENT_NOAD:
    s = ACCENT_NOAD_SIZE;
    break;

case FRACTION_NOAD:
    s = FRACTION_NOAD_SIZE;
    break;

case LEFT_NOAD:
case RIGHT_NOAD:
    t = make_left_right(q, style, max_d, max_h);
    break;

case STYLE_NODE:
    // << Change the current style and |goto delete_q| >>

case WHATSIT_NODE:
case PENALTY_NODE:
case RULE_NODE:
case DISC_NODE:
case ADJUST_NODE:
case INS_NODE:
case MARK_NODE:
case GLUE_NODE:
case KERN_NODE:
    link(p) = q;
    p = q;
    q = link(q);
    link(p) = null;
    continue; // goto done

default:
    confusion("mlist3");
}
```
