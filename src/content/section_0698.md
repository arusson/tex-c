# Section 698

That which can be displayed can also be destroyed.

```c << Cases of |flush_node_list| that arise in mlists only >>=
case STYLE_NODE:
    free_node(p, STYLE_NODE_SIZE);
    goto done;

case CHOICE_NODE:
    flush_node_list(display_mlist(p));
    flush_node_list(text_mlist(p));
    flush_node_list(script_mlist(p));
    flush_node_list(script_script_mlist(p));
    free_node(p, STYLE_NODE_SIZE);
    goto done;

case ORD_NOAD:
case OP_NOAD:
case BIN_NOAD:
case REL_NOAD:
case OPEN_NOAD:
case CLOSE_NOAD:
case PUNCT_NOAD:
case INNER_NOAD:
case RADICAL_NOAD:
case OVER_NOAD:
case UNDER_NOAD:
case VCENTER_NOAD:
case ACCENT_NOAD:
    if (math_type(nucleus(p)) >= SUB_BOX) {
        flush_node_list(info(nucleus(p)));
    }
    if (math_type(supscr(p)) >= SUB_BOX) {
        flush_node_list(info(supscr(p)));
    }
    if (math_type(subscr(p)) >= SUB_BOX) {
        flush_node_list(info(subscr(p)));
    }
    if (type(p) == RADICAL_NOAD) {
        free_node(p, RADICAL_NOAD_SIZE);
    }
    else if (type(p) == ACCENT_NOAD) {
        free_node(p, ACCENT_NOAD_SIZE);
    }
    else {
        free_node(p, NOAD_SIZE);
    }
    goto done;

case LEFT_NOAD:
case RIGHT_NOAD:
    free_node(p, NOAD_SIZE);
    goto done;

case FRACTION_NOAD:
    flush_node_list(info(numerator(p)));
    flush_node_list(info(denominator(p)));
    free_node(p, FRACTION_NOAD_SIZE);
    goto done;
```
